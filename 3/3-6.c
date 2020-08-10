#include <limits.h>
#include <stdio.h>

void my_itoa(int n, char s[], int min_len);
void reverse(char s[]);

int main() {
  char s[100];
  my_itoa(INT_MIN, s, 20);
  printf("my_itoa(%d, s, 20): %s\n", INT_MIN, s);
  return 0;
}

/* itoa: convert n to characters in s */
void my_itoa(int n, char s[], int min_len) {
  int i = 0, sign = n;

  do { /* generate digits in reverse order */
    int curr = n % 10;
    if (sign < 0)
      curr = -curr;
    s[i++] = (char)curr + '0'; /* get next digit */
  } while (n /= 10);           /* delete it */
  if (sign < 0)
    s[i++] = '-';
  while (i < min_len)
    s[i++] = ' ';
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
