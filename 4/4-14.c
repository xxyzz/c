#include <stdio.h>

#define swap(t, x, y)                                                          \
  t temp = x;                                                                  \
  x = y;                                                                       \
  y = temp

int main() {
  int x, y;
  x = 1;
  y = 2;
  swap(int, x, y);
  printf("x: %d, y: %d\n", x, y);
  return 0;
}
