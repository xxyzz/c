#include <stdio.h>

#define BUFSIZE 100

static char buf[BUFSIZE]; /* buffer for ungetch */
static int bufp = 0;      /* next free position in buf */

void ungetch(int);
void ungets(char[]);

int main() {
  ungets("I AM NOT A TOWEL!!");
  printf("%s\n", buf);
  return 0;
}

void ungetch(int c) { /* push character back on input */
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = (char)c;
}

void ungets(char s[]) {
  int i = 0;
  while (s[i] != '\0')
    ungetch(s[i++]);  // only needs ungetch
}
