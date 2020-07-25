#include <stdio.h>
#define TAB_STOP_SPACING 8

int main() {
  int c, line_len = 0, num_blanks = 0;
  while ((c = getchar()) != EOF) {
    if (c == ' ') {
      ++num_blanks;
      ++line_len;
      if (num_blanks == TAB_STOP_SPACING) {
        putchar('\t');
        num_blanks = 0;
      } else if (line_len % TAB_STOP_SPACING == 0) {
        while (num_blanks > 0) {
          putchar(' ');
          --num_blanks;
        }
      }
    } else {
      if (c == '\n') {
        num_blanks = 0;
        line_len = 0;
      } else if (c == '\t') {
        line_len += TAB_STOP_SPACING - line_len % TAB_STOP_SPACING;
        num_blanks = 0;
      } else
        ++line_len;
      while (num_blanks > 0) {
        putchar(' ');
        --num_blanks;
      }
      putchar(c);
    }
  }

  return 0;
}
