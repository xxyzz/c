#include <ctype.h>  // isalpha, isspace, isalnum
#include <stdio.h>  // EOF
#include <stdlib.h> // malloc, free
#include <string.h> // strcmp

#define MAXWORD 100
#define BUFSIZE 100
#define HASHSIZE 101

static char buf[BUFSIZE]; /* buffer for ungetch */
static int bufp = 0;      /* next free position in buf */

struct nlist {        /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void freetable(void);
int getword(char *, int);
int getch(void);
void ungetch(int c);

/* count C keywords */
int main() {
  char word[MAXWORD];
  struct nlist *np;

  while (getword(word, MAXWORD) != EOF) {
    if (strcmp(word, "#define") == 0) {
      do {
        getword(word, MAXWORD);
      } while (isspace(word[0]));
      char *name = strdup(word);
      do {
        getword(word, MAXWORD);
      } while (isspace(word[0]));
      char *value = strdup(word);
      install(name, value);
      free(name);
      free(value);
    } else if ((np = lookup(word)) != NULL) {
      printf("%s", np->defn);
    } else
      printf("%s", word);
  }
  freetable();
  return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;
  int previous = '\0', next = '\0';

  if ((c = getch()) != EOF)
    *w++ = (char)c;

  if (isalnum(c) || c == '_' || c == '#') {
    for (; --lim > 0; w++)
      if (!isalnum(*w = (char)getch()) && *w != '_') {
        ungetch(*w);
        break;
      }
  } else if (c == '/') {
    next = getch();
    if (next == '/') { // single line comment
      *--w = '\n';
      w++;
      while ((c = getch()))
        if (c == '\n')
          break;
    } else if (next == '*') { // multi-line comment
      *--w = '\0';
      while ((c = getch())) {
        if (previous == '*' && c == '/')
          break;
        previous = c;
      }
    }
  } else if (c == '"') { // string
    while ((c = getch())) {
      if (previous != '\\' && c == '"')
        break;
      previous = c;
    }
  } else {
    *w = '\0';
    return c;
  }

  *w = '\0';
  return word[0];
}

/* get a (possibly pushed back) character */
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

/* push character back on input */
void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = (char)c;
}

/* hash: form hash value for string s */
unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = (unsigned)*s + 31 * hashval;
  return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s) {
  struct nlist *np;

  for (np = hashtab[hash(s)]; np != NULL; np = np->next)
    if (strcmp(s, np->name) == 0)
      return np; /* found */
  return NULL;   /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn) {
  struct nlist *np;
  unsigned hashval;

  if ((np = lookup(name)) == NULL) { /* not found */
    np = (struct nlist *)malloc(sizeof(*np));
    if (np == NULL || (np->name = strdup(name)) == NULL)
      return NULL;
    hashval = hash(name);
    np->next = hashtab[hashval];
    hashtab[hashval] = np;
  } else                    /* already there */
    free((void *)np->defn); /* free previous defn */
  if ((np->defn = strdup(defn)) == NULL)
    return NULL;
  return np;
}

void freetable() {
  struct nlist *np;
  for (int i = 0; i < HASHSIZE; i++) {
    np = hashtab[i];
    while (np != NULL) {
      struct nlist *tmp = np->next;
      free(np->defn);
      free(np->name);
      free(np);
      np = tmp;
    }
  }
}
