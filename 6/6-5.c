#include <stdio.h>
#include <stdlib.h> // malloc, free
#include <string.h> //strcmp
#define HASHSIZE 101

struct nlist {        /* table entry: */
  struct nlist *next; /* next entry in chain */
  char *name;         /* defined name */
  char *defn;         /* replacement text */
};

static struct nlist *hashtab[HASHSIZE]; /* pointer table */

unsigned hash(char *);
struct nlist *lookup(char *);
struct nlist *install(char *, char *);
void undef(char *);

int main() {
  struct nlist *np;
  install("biggest fear", "snake");
  install("biggest fear", "snake-clowns");
  install("password", "Iron Man sucks!");
  np = lookup("biggest fear");
  printf("lookup \"biggest fear\": %s\n", np->defn);
  np = lookup("password");
  printf("lookup \"password\": %s\n", np->defn);
  undef("password");
  np = lookup("password");
  printf("lookup \"password\": %s\n", np ? np->defn : "not found");
  return 0;
}

/* remove a name and definition from the table */
void undef(char *s) {
  struct nlist *np;
  if ((np = lookup(s)) != NULL) {
    hashtab[hash(s)] = np->next;
    free(np->defn);
    free(np->name);
    free(np);
  }
}

/* hash: form hash value for string s */
unsigned hash(char *s) {
  unsigned hashval;

  for (hashval = 0; *s != '\0'; s++)
    hashval = (unsigned)s + 31 * hashval;
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
