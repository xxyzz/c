#include <stdio.h>

int main() {
  int c, inside_single = 0, inside_multi = 0, single_quote = 0, double_quote= 0, previous = ' ';
  while ((c = getchar()) != EOF) {
    if (inside_single) { // inside single line comment
      if (c == '\n')
        inside_single = 0;
    } else if (inside_multi) { // inside multi-line comment
      if (previous == '*' && c == '/')
        inside_multi = 0;
    } else if (single_quote) {
      if (previous != '\\' && c == '\'')
        single_quote = 0;
      putchar(c);
    } else if (double_quote) {
      if (previous != '\\' && c == '"')
        double_quote = 0;
      putchar(c);
    } else {
      if (c == '/') {
        int next = getchar();
        if (next == '/')
          inside_single = 1;
        else if (next == '*')
          inside_multi = 1;
        else if (next == EOF)
          break;
      } else if (c == '"') {
        double_quote = 1;
        putchar(c);
      } else if (c == '\'') {
        single_quote = 1;
        putchar(c);
      } else
        putchar(c);
    }
    previous = c;
  }

  return 0;
}
