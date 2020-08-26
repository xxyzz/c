#include <stdio.h>

int my_isupper(int);

int main() {
  printf("%d\n", my_isupper('p'));
  return 0;
}

int my_isupper(int c) {
  // save space
  return c >= 'A' && c <= 'Z';

  // save time
  // return table[c];
}
