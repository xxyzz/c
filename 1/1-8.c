#include <stdio.h>

/* count blanks, tabs and newlines in input */
int main() {
  int c, blanks = 0, tabs = 0, newlines = 0;

  while ((c = getchar()) != EOF) {
    if (c == ' ')
      ++blanks;
    if (c == '\t')
      ++tabs;
    if (c == '\n')
      ++newlines;
  }
  printf("blanks: %d, tabs: %d, newlines: %d\n", blanks, tabs, newlines);
}
