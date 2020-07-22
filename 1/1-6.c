#include <stdio.h>

/* copy input to output */
int main() {
  int c;

  while (c = getchar() != EOF)
    printf("%d\n", c); // 1
  printf("%d\n", c);   // 0, command + d
}
