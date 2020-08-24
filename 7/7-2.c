#include <ctype.h> // isprint
#include <stdio.h>

#define LINELIM 80

int main() {
  int c, len = 0;
  while ((c = getchar()) != EOF) {
    if (isprint(c) || c == '\n') {
      putchar(c);
      if (c == '\n')
        len = 0;
    } else
      printf("0x%o", c);
    len++;
    if (len >= LINELIM) {
      putchar('\n');
      len = 0;
    }
  }
  return 0;
}
