#include <stdio.h>
#define TAB_STOP_SPACING 8
/*
 * Tab stop spacing is unchanged here therefore
 * a symbolic parameter fits well. If it ever needs
 * to be modified, use a variable instead.
 *
 * What the heck is tab stop:
 * https://en.wikipedia.org/wiki/Tab_stop
 * https://en.wikipedia.org/wiki/Tab_key#Tab_characters
 * https://support.apple.com/guide/pages/set-tab-stops-tan39ebf390a/mac
 */

int main() {
  int c, line_len = 0;
  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      int num_blanks = TAB_STOP_SPACING - line_len % TAB_STOP_SPACING;
      while (num_blanks-- > 0) {
        putchar(' ');
        ++line_len;
      }
    } else if (c == '\n') {
      putchar(c);
      line_len = 0;
    } else {
      putchar(c);
      ++line_len;
    }
  }
}

