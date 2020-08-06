#include <limits.h>
#include <stdio.h>

void my_itoa(int n, char s[]);

int main() {
  char s[100];
  my_itoa(INT_MIN, s);
  printf("%d to string: %s\n", INT_MIN, s);
  return 0;
}

void my_itoa(int n, char s[]) {
  static int i = 0;
  int curr = n % 10;
  if (n < 0) {
    curr = -curr;
    if (!i)
      s[i++] = '-';
  }
  if (n /= 10)
    my_itoa(n, s);
  s[i++] = (char)curr + '0';
  if (!n)
    s[i] = '\0';
}
