#include <ctype.h> // isdigit, isalpha
#include <math.h>  // fmod
#include <stdio.h>
#include <stdlib.h> // atof
#include <string.h> // strlen

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100

static int sp = 0;         /* next free stack position */
static double val[MAXVAL]; /* value stack */
static char buf[BUFSIZE];  /* buffer for ungetch */
static int bufp = 0;       /* next free position in buf */
static double vars[26];

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

/* reverse Polish calculator */
int main() {
  int type;
  double op2;
  char s[MAXOP], var = '\0';

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
      // store the most recently printed value to variable 'r'
      vars['r' - 'a'] = pop();
      printf("\t%.8g\n", vars['r' - 'a']); // print result
      break;
    case '=': // assign value to variable: 'a' 1 =
      if (isalpha(var))
        vars[tolower(var) - 'a'] = pop();
      else
        printf("unknown variable: %c\n", var);
      break;
    default:
      if (isalpha(type)) {
        push(vars[tolower(type) - 'a']);
        var = (char)type;
      }
      else
        printf("error: unknown command %s\n", s);
      break;
    }
  }
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

  while ((s[0] = c = (char)getch()) == ' ' || c == '\t')
    ;
  s[1] = '\0';
  if (!isdigit(c) && c != '.' && c != '-')
    return c; // operator or variable
  if (c == '-') {
    if (isdigit(c = getch()) || c == '.')
      s[++i] = (char)c; // negative number
    else {
      if (c != EOF)
        ungetch(c);
      return '-'; // minus sign
    }
  }
  if (isdigit(c)) /* collect integer part */
    while (isdigit(s[++i] = c = (char)getch()))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(s[++i] = c = (char)getch()))
      ;
  s[i] = '\0';
  if (c != EOF)
    ungetch(c);
  return NUMBER;
}

int getch(void) { /* get a (possibly pushed back) character */
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) { /* push character back on input */
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = (char)c;
}
