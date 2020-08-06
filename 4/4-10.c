#include <ctype.h> /* isdigit  */
#include <math.h>  /* fmod */
#include <stdio.h>  /* getline  */
#include <stdlib.h> /* atof, free */

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100 /* maximum depth of val stack */

static int sp = 0;         /* next free stack position */
static double val[MAXVAL]; /* value stack */

static char *line = NULL;
static int li = 0;
static size_t len = 0;

int getop(char[]);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main() {
  int type;
  double op2;
  char s[MAXOP];

  while ((type = getop(s)) != EOF) {
    switch (type) {
    case NUMBER:
      push(atof(s));
      break;
    case '+':
      push(pop() + pop());
      break;
    case '*':
      push(pop() * pop());
      break;
    case '-':
      op2 = pop();
      push(pop() - op2);
      break;
    case '/':
      op2 = pop();
      if (op2 != 0.0)
        push(pop() / op2);
      else
        printf("error: zero divisor\n");
      break;
    case '%':
      op2 = pop();
      push(fmod(pop(), op2));
      break;
    case '\n':
      printf("\t%.8g\n", pop()); // print result
      break;
    default:
      printf("error: unknown command %s\n", s);
      break;
    }
  }
  free(line);
  return 0;
}

/* push: push f onto value stack */
void push(double f) {
  if (sp < MAXVAL)
    val[sp++] = f;
  else
    printf("error: stack full, can′t push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void) {
  if (sp > 0)
    return val[--sp];
  else {
    printf("error: stack empty\n");
    return 0.0;
  }
}

/* getop: get next operator or numeric operand */
int getop(char s[]) {
  int i = 0, c;

  if (line == NULL || line[li] == '\0') {
    if (getline(&line, &len, stdin) == -1)
      return EOF;
    else
      li = 0;
  }

  while ((s[0] = c = line[li++]) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-')
    return c; /* not a number */
  if (c == '-') {
    if (isdigit(c = line[li++]) || c == '.')
      s[++i] = (char)c; // negative number
    else {
      if (c != EOF)
        li--;
      return '-'; // minus sign
    }
  }
  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = line[li++]))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = line[li++]))
      ;
  s[i] = '\0';
  if (c != EOF)
    li--;
  return NUMBER;
}
