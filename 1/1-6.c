#include <stdio.h>

/* copy input to output */
int main() {
  int c;

  while (c = getchar() != EOF)
    printf("%d\n", c); // 1
  printf("%d\n", c);   // 0, command + d

  /*
   * sizeof(int): 4
   * sizeof(EOF): 4
   * sizeof(char): 1
   * that's why c is a int instead of a char
   */
}
