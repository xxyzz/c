#include <stdio.h>

int bitcount(unsigned x);

int main() {
  // 1001 x = 9, ++b
  // 1000 x - 1 = 8
  // 1000 x = x & x - 1 = 8, ++b
  // 0111 x - 1 = 7
  // 0000 x = x & x - 1 = 0
  printf("bitcount(9), %d\n", bitcount(9));
  return 0;
}

/* bitcount:  count 1 bits in x */
int bitcount(unsigned x) {
  int b;
  for (b = 0; x != 0; x &= x - 1)
    ++b;
  return b;
}
