#include <stdio.h>

unsigned invert(unsigned x, int p, int n);

int main() {
  // 4095: 1111 1111 1111
  // 3855: 1111 0000 1111
  // index      7654 3210
  printf("invert(4095, 7, 4): %d\n", invert(4095, 7, 4));

  printf("-1L < 1U: %d\n", -1L < 1U);
  // 1, 1U(unsigned int) -> 1(signed long)

  printf("-1L < 1UL: %d\n", -1L < 1UL);
  // 0, -1L(signed long) -> large number(unsigned long)
  return 0;
}

unsigned invert(unsigned x, int p, int n) {
  return x ^ (unsigned)(~(~0 << n) << (p + 1 - n));
}

/*
 * 0 ^ 0 = 0, 1 ^ 0 = 1
 * 0 ^ 1 = 1, 1 ^ 1 = 0 invert
 * ~0 << n: 1111 0000
 * ~(~0 << n): 0000 1111
 * ~(~0 << n) << (p + 1 - n): 0000 1111 0000
 * x ^ ~(~(~0 << n) << (p + 1 - n)): xxxx ~xxxx xxxx
 */
