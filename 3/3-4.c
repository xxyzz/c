#include <limits.h>
#include <stdio.h>

/*
 * positive number can't represent the smallest negative number
 * -4: 100, 3: 011
 */

void my_itoa(int n, char s[]);
void reverse(char s[]);

int main() {
  char s[100];
  my_itoa(INT_MIN, s);
  printf("my_itoa(%d, s): %s\n", INT_MIN, s);
  return 0;
}

/* itoa: convert n to characters in s */
void my_itoa(int n, char s[]) {
  int i = 0, sign = n;
  do { /* generate digits in reverse order */
    int curr = n % 10;
    if (sign < 0)
      curr = -curr;
    s[i++] = (char)curr + '0'; /* get next digit */
  } while (n /= 10);           /* delete it */
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
