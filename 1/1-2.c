#include <stdio.h>

int main() {
  printf("\c\n");
  // 1-2.c:4:14: warning: unknown escape sequence '\c'
  // [-Wunknown-escape-sequence]

  // just print a "c"
}
