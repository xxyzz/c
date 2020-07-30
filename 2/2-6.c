#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);

int main() {
  // 4095: 1111 1111 1111
  // 4031: 1111 1011 1111
  // index      7654 3210
  printf("setbits(4095, 7, 4, 4031): %d\n", setbits(4095, 7, 4, 4031));
  return 0;
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
  return (x & (unsigned)~(~(~0 << n) << (p + 1 - n))) |
         (y & (unsigned)(~(~0 << n) << (p + 1 - n)));
}

/*
 * ~0 << n: 1111 0000
 * ~(~0 << n): 0000 1111
 * ~(~0 << n) << (p + 1 - n): 0000 1111 0000
 * ~(~(~0 << n) << (p + 1 - n)): 1111 0000 1111
 * x & ~(~(~0 << n) << (p + 1 - n)): xxxx 0000 xxxx
 * y & (~(~0 << n) << (p + 1 - n)): 0000 yyyy 0000
 */
