#include <stdio.h>

int wordlength(void);
unsigned rightrot(unsigned x, int n);

int main() {
  printf("word length: %d\n", wordlength()); // 32
  // 0000 0000 0000 0000 0000 0000 0000 0011 = 3
  // 0011 0000 0000 0000 0000 0000 0000 0000 = 805306368
  printf("rightrot(3, 4): %d\n", rightrot(3, 4));
  return 0;
}

int wordlength() {
  int len;
  unsigned i = (unsigned)~0;
  for (len = 1; (i >>= 1) > 0; len++)
    ;
  return len;
}

unsigned rightrot(unsigned x, int n) {
  int word_len = wordlength();
  if ((n %= word_len) > 0) {
    unsigned right_bits = x & (unsigned)~(~0 << n);
    right_bits <<= (word_len - n);
    x = (x >> n) | right_bits;
  }
  return x;
}
