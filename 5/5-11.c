#include <stdio.h>
#include <stdlib.h> // atoi

#define DEFAULT_TAB_STOP_SPACING 8
#define MAX_TABS 10

int blanks(int use_default, int *tabs, int tabs_len, int len);
int tabs_len_sum(int *tabs, int tabs_len);

int main(int argc, char *argv[]) {
  int c, line_len = 0, use_default = 1;
  int tabs[MAX_TABS], tabs_len = 0;

  if (argc > 1) {
    use_default = 0;
    for (int i = 0; i < argc - 1 && i < MAX_TABS; i++) {
      tabs[i] = atoi(argv[i + 1]);
      tabs_len++;
    }
  }

  // detab: replace tab with blanks
  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      int num_blanks = blanks(use_default, tabs, tabs_len, line_len);
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
  return 0;
}

int blanks(int use_default, int *tabs, int tabs_len, int len) {
  int sum = 0;
  if (use_default)
    return DEFAULT_TAB_STOP_SPACING - len % DEFAULT_TAB_STOP_SPACING;
  else {
    while (tabs_len-- > 0) {
      sum += *tabs++;
      if (sum > len)
        return sum - len;
    }
  }
  return DEFAULT_TAB_STOP_SPACING - (len - sum) % DEFAULT_TAB_STOP_SPACING;
}

int tabs_len_sum(int *tabs, int tabs_len) {
  int sum = 0;
  while (tabs_len-- > 0)
    sum += *tabs++;
  return sum;
}
