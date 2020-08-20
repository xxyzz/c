#include <ctype.h>  // isalpha, isspace, isalnum
#include <stdio.h>  // EOF
#include <stdlib.h> // strtol, malloc, free
#include <string.h> // strcmp, strlen

#define MAXWORD 100
#define BUFSIZE 100

struct tnode { /* the tree node: */
  char *word;  /* points to the text */
  int print;   /* print it or not */
  char pad[sizeof(char *) - sizeof(int)];
  struct tnode *left;  /* left child */
  struct tnode *right; /* right child */
};

static char buf[BUFSIZE]; /* buffer for ungetch */
static int bufp = 0;      /* next free position in buf */

int getword(char *, int);
int getch(void);
void ungetch(int c);
struct tnode *addtree(struct tnode *, char *, size_t, int *);
void treeprint(struct tnode *);
struct tnode *talloc(void);
int compare(char *, struct tnode *, size_t, int *);
void freetree(struct tnode *);

/* count C keywords */
int main(int argc, char *argv[]) {
  struct tnode *root = NULL;
  char word[MAXWORD];
  size_t compare_len = 6;
  int print = 0;
  if (argc == 2)
    compare_len = (size_t)strtol(argv[1], NULL, 10);

  while (getword(word, MAXWORD) != EOF) {
    if (isalpha(word[0]) && strlen(word) >= compare_len)
      root = addtree(root, word, compare_len, &print);
    print = 0;
  }

  treeprint(root);
  freetree(root);
  return 0;
}

/* compare two strings and decide whether print it */
int compare(char *s1, struct tnode *p, size_t len, int *print) {
  size_t i;
  char *s2 = p->word;
  for (i = 0; *s1 == *s2; i++, s1++, s2++) {
    if (*s1 == '\0')
      return 0;
  }
  if (i >= len) {
    *print = 1;
    p->print = 1;
  }
  return *s1 - *s2;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w, size_t len, int *print) {
  int cond;
  if (p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->left = p->right = NULL;
    p->print = *print;
  } else if ((cond = compare(w, p, len, print)) > 0)
    p->right = addtree(p->right, w, len, print);
  else if (cond < 0)
    p->left = addtree(p->left, w, len, print);
  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
  if (p) {
    treeprint(p->left);
    if (p->print)
      printf("%s\n", p->word);
    treeprint(p->right);
  }
}

/* free a tree, can't free a region */
void freetree(struct tnode *p) {
  if (p) {
    freetree(p->left);
    free(p->word);
    free(p);
    freetree(p->right);
  }
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;
  int previous = '\0', next = '\0';

  while (isspace(c = getch()))
    ;
  if (c != EOF && c != '#')
    *w++ = (char)c;

  if (isalpha(c) || c == '_' || c == '#') {
    for (; --lim > 0; w++)
      if (!isalnum(*w = (char)getch()) && *w != '_') {
        ungetch(*w);
        break;
      }
  } else if (c == '/') {
    next = getch();
    if (next == '/') { // single line comment
      while ((c = getch()))
        if (c == '\n')
          break;
    } else if (next == '*') { // multi-line comment
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
  } else if (c == '\'') { // char: 'x', '\t'
    int after_quote = 0, pre = '\0', prepre = '\0';
    while ((c = getch())) {
      ++after_quote;
      if (c == '\'' && pre != '\\' && after_quote == 2)
        break;
      else if (c == '\'' && prepre == '\\' && after_quote == 3)
        break;
      prepre = pre;
      pre = c;
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
