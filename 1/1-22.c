#include <stdio.h>

#define TAB_STOP_SPEACING 8
#define FOLD_THRESHOLD 10

void print_line(char s[], int len);

int main() {
  char s[FOLD_THRESHOLD];
  int c, line_len = 0, last_nonblank = 0;

  while ((c = getchar()) != EOF) {
    if (c == '\n') {
      print_line(s, line_len);
      line_len = last_nonblank = 0;
    } else if (c == '\t') {
      // replace tab with blanks
      int blanks = TAB_STOP_SPEACING - line_len % TAB_STOP_SPEACING;
      for (int i = 0; i < blanks; i++)
        s[line_len++] = ' ';
    } else {
      s[line_len++] = (char)c;
      if (c != ' ')
        last_nonblank = line_len;
    }

    if (line_len >= FOLD_THRESHOLD) {
      print_line(s, last_nonblank);
      line_len = last_nonblank = 0;
    }
  }

  return 0;
}

void print_line(char s[], int len) {
  for (int i = 0; i < len; i++)
    putchar(s[i]);
  if (len > 0)
    putchar('\n');
}
