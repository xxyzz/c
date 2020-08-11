#include <ctype.h> // isdigit
#include <math.h>  /* fmod */
#include <stdio.h>
#include <stdlib.h> // atof
#include <string.h> // strlen

#define NUMBER '0' /* signal that a number was found */

void push(double);
double pop(void);

// $ ./5-10.out  2  3  4  +  \*
int main(int argc, char *argv[]) {
  int c, type;
  double op2;
  while (--argc > 0) {
    if (!isdigit(c = **++argv) && strlen(*argv) == 1)
      type = c;
    else
      type = NUMBER;
    switch(type) {
    case NUMBER:
      push(atof(*argv));
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
    default:
      printf("error: unknown command %s\n", *argv);
      break;
    }
    if (argc == 1)
      printf("\t%.8g\n", pop()); // print result
  }
  return 0;
}

#define MAXVAL 100 /* maximum depth of val stack */

static int sp = 0;         /* next free stack position */
static double val[MAXVAL]; /* value stack */

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
