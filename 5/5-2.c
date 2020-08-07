#include <ctype.h>
#include <math.h>
#include <stdio.h>

#define BUFSIZE 100

static char buf[BUFSIZE];  /* buffer for ungetch */
static int bufp = 0;       /* next free position in buf */

int getch(void);
void ungetch(int);
int getfloat(double *pn);

int main() {
  double n = 0;
  getfloat(&n);
  printf("buf: %s\n", buf);
  printf("n: %g\n", n);
  return 0;
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

/* getfloat: get next float number from input into *pn */
int getfloat(double *pn) {
  int c, sign, power = 1, exp = 0, exp_sign = 1;

  while (isspace(c = getch())) /* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.') {
    ungetch(c); /* it′s not a number */
    return 0;
  }
  sign = (c == '-') ? -1 : 1;
  if (c == '+' || c == '-') {
    int sign_char = c;
    c = getch();
    if (!isdigit(c)) {
      if (c != EOF)
        ungetch(c);
      ungetch(sign_char);
      return sign_char;
    }
  }
  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  if (c == '.') {
    c = getch();
    for (; isdigit(c); c = getch()) {
      *pn = 10 * *pn + (c - '0');
      power *= 10;
    }
  }
  if (tolower(c) == 'e') {
    c = getch();
    if (c == '+' || c == '-') {
      if (c == '-')
        exp_sign = -1;
      c = getch();
    }
    for (; isdigit(c); c = getchar())
      exp = exp * 10 + (c - '0');
  }
  *pn *= sign;
  *pn /= power;
  if (exp) {
    if (exp_sign == -1)
      *pn /= pow(10, exp);
    else
      *pn *= pow(10, exp);
  }

  if (c != EOF)
    ungetch(c);
  return c;
}
