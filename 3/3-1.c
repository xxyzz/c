#include <stdio.h>

int binsearch(int x, int v[], int n);

int main() {
  int a[] = {0, 1, 2, 3, 4};
  printf("binsearch(3, [0, 1, 2, 3, 4]): %d\n", binsearch(3, a, 5));
  return 0;
}

/* binsearch:  find x in v[0] <= v[1] <= ... <= v[n−1] */
int binsearch(int x, int v[], int n) {
  int low = 0, high = n - 1, mid = (low + high) / 2;
  while (low <= high && v[mid] != x) {
    if (x < v[mid])
      high = mid - 1;
    else
      low = mid + 1;
    mid = (low + high) / 2;
  }
  return (v[mid] == x) ? mid : -1;
}
