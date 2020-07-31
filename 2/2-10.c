#include <stdio.h>

int lower(int c);

int main() {
  printf("lower('C'): %c\n", lower('C'));
  return 0; }

int lower(int c) {
  return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}
