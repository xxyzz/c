#include <ctype.h>  // isalpha, tolower
#include <stdio.h>  // EOF, getline
#include <stdlib.h> // strtol, malloc, free
#include <string.h> // strcasecmp, strlen, strsqp

struct qnode {
  struct qnode *next;
  long linenum;
};

struct queue {
  struct qnode *first;
  struct qnode *last;
};

struct tnode {         /* the tree node: */
  char *word;          /* points to the text */
  struct queue lines;  /* line numbers queue */
  struct tnode *left;  /* left child */
  struct tnode *right; /* right child */
};

void enqueue(struct queue *q, long);
struct qnode *dequeue(struct queue *q);
struct tnode *addtree(struct tnode *, const char *, long);
void treeprint(struct tnode *);
struct tnode *talloc(void);
int searchtree(struct tnode *, const char *);
int isword(char *s);

/* print each word with line numbers */
int main() {
  struct tnode *root = NULL, *noise = NULL;
  char *line = NULL, *token, *tofree;
  size_t len = 0;
  long lines_num = 1;
  ssize_t nread;

  noise = addtree(noise, "and", 0);
  addtree(noise, "the", 0);

  while ((nread = getline(&line, &len, stdin)) != -1) {
    tofree = line;
    while ((token = (strsep(&line, " \t"))) != NULL)
      if (*token != '\0' && isword(token) && !searchtree(noise, token))
        root = addtree(root, token, lines_num);
    lines_num++;
  }

  free(line);
  treeprint(root);
  return 0;
}

/* addtree: add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, const char *w, long line) {
  int cond;
  if (p == NULL) {
    p = talloc();
    p->word = strdup(w);
    p->left = p->right = NULL;
    enqueue(&p->lines, line);
  } else if ((cond = strcmp(w, p->word)) > 0)
    p->right = addtree(p->right, w, line);
  else if (cond < 0)
    p->left = addtree(p->left, w, line);
  else
    enqueue(&p->lines, line);
  return p;
}

/* treeprint: in-order print of tree p */
void treeprint(struct tnode *p) {
  if (p != NULL) {
    treeprint(p->left);
    printf("%s: ", p->word);
    struct qnode *n;
    while ((n = dequeue(&p->lines)) != NULL) {
      printf("%ld ", n->linenum);
      free(n);
    }
    printf("\n");
    treeprint(p->right);
    free(p->word);
    free(p);
  }
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
  struct tnode *n = (struct tnode *)malloc(sizeof(struct tnode));
  n->lines.first = NULL;
  n->lines.last = NULL;
  return n;
}

// Add item to the end of the list.
void enqueue(struct queue *q, long linenum) {
  struct qnode *oldlast = q->last;
  q->last = malloc(sizeof(struct qnode));
  q->last->linenum = linenum;
  q->last->next = NULL;
  if (q->first == NULL)
    q->first = q->last;
  else
    oldlast->next = q->last;
}

// Remove item from the beginning of the list.
struct qnode *dequeue(struct queue *q) {
  if (q->first == NULL)
    return NULL;
  struct qnode *oldfirst = q->first;
  q->first = q->first->next;
  return oldfirst;
}

int isword(char *s) {
  while (*s)
    if (!isalpha(*s++))
      return 0;
  return 1;
}
