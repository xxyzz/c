#include <stdio.h>  // getline
#include <stdlib.h> // stroul, malloc, free
#include <string.h> // strdup

typedef struct node_t {
  struct node_t *next;
  char *line;
} Node;

typedef struct queue_t {
  Node *first;
  Node *last;
  size_t size;
  size_t capaticy;
} Queue;

void enqueue(Queue *q, char *s);
Node *dequeue(Queue *q);

int main(int argc, char *argv[]) {
  // get user input
  size_t lines_num = 10;
  if (argc > 1 && *argv[1] == '-')
    lines_num = strtoul(argv[1] + 1, NULL, 10);

  char *line;
  size_t linecap = 0;
  ssize_t linelen;
  Queue q;
  q.size = 0;
  q.capaticy = lines_num;

  // get lines
  while ((linelen = getline(&line, &linecap, stdin)) > 0)
    enqueue(&q, line);

  // print lines
  for (size_t j = 0; j < lines_num; j++) {
    Node *n = dequeue(&q);
    if (n) {
      if (n->line) {
        printf("%s", n->line);
        free(n->line);
      }
      free(n);
    } else
      break;
  }

  free(line);
  return 0;
}

// Add item to the end of the list.
void enqueue(Queue *q, char *s) {
  if (q->size == q->capaticy)
    dequeue(q);
  Node *oldlast = q->last;
  q->last = malloc(sizeof(Node));
  q->last->line = strdup(s);
  q->last->next = NULL;
  if (q->size == 0)
    q->first = q->last;
  else
    oldlast->next = q->last;
  q->size++;
}

// Remove item from the beginning of the list.
Node *dequeue(Queue *q) {
  if (q->size == 0)
    return NULL;
  Node *oldfirst= q->first;
  q->first = q->first->next;
  q->size--;
  return oldfirst;
}
