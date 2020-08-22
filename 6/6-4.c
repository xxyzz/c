#include <ctype.h>  // isalpha, tolower
#include <stdio.h>  // EOF, getline
#include <stdlib.h> // strtol, malloc, free
#include <string.h> // strcasecmp, strlen, strsqp

struct tnode { /* the tree node: */
  char *word;  /* points to the text */
  int count;
  char pad[sizeof(char *) - sizeof(int)];
  struct tnode *left;  /* left child */
  struct tnode *right; /* right child */
};

struct tnode *addtree(struct tnode *, const char *, int *);
struct tnode *talloc(void);
int searchtree(struct tnode *, const char *);
void freetree(struct tnode *);
int isword(char *);
void tree_to_array(struct tnode *, struct tnode **);
void swap(void *v[], int, int);
void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int compare(struct tnode *n1, struct tnode *n2);

/* print each word with line numbers */
int main() {
  struct tnode *root = NULL, *noise = NULL, **wordarr;
  char *line = NULL, *token, *tofree = NULL;
  size_t len = 0;
  int wordnums = 0;
  ssize_t nread;

  noise = addtree(noise, "and", 0);
  addtree(noise, "the", 0);

  while ((nread = getline(&line, &len, stdin)) != -1) {
    tofree = line;
    while ((token = (strsep(&line, " \t"))) != NULL)
      if (*token != '\0' && isword(token) && !searchtree(noise, token))
        root = addtree(root, token, &wordnums);
  }

  wordarr = malloc((size_t)wordnums * sizeof(struct tnode));
  tree_to_array(root, wordarr);
  my_qsort((void **)wordarr, 0, wordnums - 1, (int (*)(void *, void *))compare);
  for (int i = 0; i < wordnums; i++)
    printf("%s: %d\n", wordarr[i]->word, wordarr[i]->count);
  free(tofree);
  freetree(root);
  free(wordarr);
  return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, const char *w, int *wordnums) {
  int cond;
  if (p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->left = p->right = NULL;
    p->count = 1;
    if (wordnums)
      (*wordnums)++;
  } else if ((cond = strcmp(w, p->word)) > 0)
    p->right = addtree(p->right, w, wordnums);
  else if (cond < 0)
    p->left = addtree(p->left, w, wordnums);
  else
    p->count++;
  return p;
}

int searchtree(struct tnode *p, const char *s) {
  int cond;
  if (p != NULL) {
    if ((cond = strcasecmp(s, p->word)) > 0)
      return searchtree(p->right, s);
    else if (cond < 0)
      return searchtree(p->left, s);
    else
      return 1;
  }
  return 0;
}

/* talloc: make a tnode */
struct tnode *talloc(void) {
  return (struct tnode *)malloc(sizeof(struct tnode));
}

/* free a tree, can't free a region */
void freetree(struct tnode *p) {
  if (p != NULL) {
    freetree(p->left);
    free(p->word);
    free(p);
    freetree(p->right);
  }
}

void tree_to_array(struct tnode *n, struct tnode **w) {
  static size_t i = 0;
  if (n != NULL) {
    tree_to_array(n->left, w);
    w[i++] = n;
    tree_to_array(n->right, w);
  }
}

int isword(char *s) {
  while (*s)
    if (!isalpha(*s++))
      return 0;
  return 1;
}

/* my_sort: sort v[left]...v[right] into decreasing order */
void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *)) {
  int i, last;

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++)
    if ((*comp)(v[i], v[left]) > 0)
      swap(v, ++last, i);
  swap(v, left, last);
  my_qsort(v, left, last - 1, comp);
  my_qsort(v, last + 1, right, comp);
}

void swap(void *v[], int i, int j) {
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

int compare(struct tnode *n1, struct tnode *n2) {
  return n1->count - n2->count;
}
