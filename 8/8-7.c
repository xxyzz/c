#include "malloc.h"
#include <limits.h>
#include <stdio.h>

int main() {
  int *a;
  a = my_malloc(-1);
  if (a == NULL)
    printf("my_malloc(-1) passed\n");
  else
    printf("my_malloc(-1) failed\n");
  a = my_malloc(UINT_MAX);
  if (a == NULL)
    printf("my_malloc(UINT_MAX) passed\n");
  else
    printf("my_malloc(UINT_MAX) failed\n");
  my_free(NULL);
  a = my_malloc(1);
  if (a == NULL)
    printf("my_malloc(1) failed\n");
  my_free(a);
  return 0;
}
