#include <stdio.h>

int main() {
  int c, inside_single = 0, inside_multi = 0, previous = ' ';
  while((c = getchar()) != EOF) {
    if (inside_single) {
      if (c == '\n')
        inside_single = 0;
    } else if (inside_multi) {
      if (previous == '*' && c == '/')
        inside_multi = 0;
    } else {
      if (c == '/') {
        int next = getchar();
        if (next == '/')
          inside_single = 1;
        else if (next == '*')
          inside_multi = 1;
        else if (next == EOF)
          break;
      } else
        putchar(c);
    }
    previous = c;
  }

  return 0;
}
