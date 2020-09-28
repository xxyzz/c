#include "malloc.h"
#include <stdio.h>

int main() {
  char a[100];
  printf("a: %p\n", a);
  bfree(a, 100); // add 6 units: 100 / sizeof(Header) = 100 / 16 = 6
  char *p;
  if ((p = my_malloc(5 * sizeof(Header))) == NULL) // request 5 units
    printf("my_malloc failed\n");
  printf("p: %p\n", (Header *)p - 1);
  return 0;
}
