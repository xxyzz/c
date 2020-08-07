#include <ctype.h>
#include <stdio.h>

#define BUFSIZE 100

static char buf[BUFSIZE];  /* buffer for ungetch */
static int bufp = 0;       /* next free position in buf */

int getch(void);
void ungetch(int);
int getint(int *pn);

int main() {
  int n = 0;
  getint(&n);
  printf("%s\n", buf);
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

/* getint: get next integer from input into *pn */
int getint(int *pn) {
  int c, sign;

  while (isspace(c = getch())) /* skip white space */
    ;
  if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
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
  *pn *= sign;
  if (c != EOF)
    ungetch(c);
  return c;
}
