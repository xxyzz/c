#include <stdio.h> // getchar

static char buf = '\0';  /* buffer for ungetch */

int getch(void);
void ungetch(int);

int main() {
  ungetch('a');
  printf("buf: %c\n", buf);
  printf("getchar(): %c\n", getch());
  return 0;
}

int getch(void) { /* get a (possibly pushed back) character */
  if (buf != '\0') {
    char temp = buf;
    buf = '\0';
    return temp;
  } else
    return getchar();
}

void ungetch(int c) { /* push character back on input */
  if (buf != '\0')
    printf("ungetch: too many characters\n");
  else
    buf = (char)c;
}
