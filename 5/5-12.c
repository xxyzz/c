#include <stdio.h>
#include <stdlib.h> // atoi
#include <ctype.h>

#define DEFAULT_TAB_STOP_SPACING 8

int blanks(int use_default, int custom_space, int start_at, int len);
int tabs_len_sum(int *tabs, int tabs_len);

int main(int argc, char *argv[]) {
  int c, line_len = 0, use_default = 1;
  int custom_space = 0, start_at = 0;

  if (argc == 3) {
    use_default = 0;
    for (int i = 1; i < argc; i++) {
      if (*argv[i] == '-')
        start_at = atoi(argv[i] + 1);
      else if (*argv[i] == '+')
        custom_space = atoi(argv[i] + 1);
    }
  }

  // detab: replace tab with blanks
  while ((c = getchar()) != EOF) {
    if (c == '\t') {
      int num_blanks = blanks(use_default, custom_space, start_at, line_len);
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

int blanks(int use_default, int custom_space, int start_at, int len) {
  if (use_default || (!use_default && len < start_at))
    return DEFAULT_TAB_STOP_SPACING - len % DEFAULT_TAB_STOP_SPACING;
  return custom_space - (len - start_at) % custom_space;
}

int tabs_len_sum(int *tabs, int tabs_len) {
  int sum = 0;
  while (tabs_len-- > 0)
    sum += *tabs++;
  return sum;
}
