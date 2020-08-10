#include <limits.h>
#include <stdio.h>

void my_itob(int n, char s[], int b);
void reverse(char s[]);

int main() {
  char s[100];
  my_itob(INT_MIN, s, 16);
  printf("my_itob(%d, s, 16): %s\n", INT_MIN, s);
  my_itob(-4, s, 2);
  printf("my_itob(-4, 2, 16): %s\n", s);
  my_itob(3, s, 2);
  printf("my_itob(3, 2, 16): %s\n", s);
  return 0;
}

void my_itob(int n, char s[], int b) {
  int i = 0, sign = n;
  do {
    int curr = n % b;
    if (curr < 0)
      curr = -curr;
    s[i++] = (curr < 10) ? (char)curr + '0'
                         : (char)curr - 10 + 'A'; /* right most bit */
  } while (n /= b);                               /* delete it */
  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s);
}

void reverse(char s[]) {
  int len;
  for (len = 0; s[len] != '\0'; len++)
    ;
  for (int i = 0; i < len / 2; i++) {
    char temp = s[i];
    s[i] = s[len - i - 1];
    s[len - i - 1] = temp;
  }
}
