#include <stdio.h>
#include "malloc.h"

int main() {
  int *a;
  size_t n = 10;
  a = my_calloc(n, sizeof(int));
  for (size_t i = 0; i < n; i++)
    printf("%d\n", a[i]);
  return 0;
}
