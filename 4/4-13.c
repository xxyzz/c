#include <stdio.h>
#include <string.h>

void reverse(size_t i, size_t len, char s[]);

int main() {
  char s[] = "Be vigilant..!";
  reverse(0, strlen(s), s);
  printf("%s\n", s);
  return 0;
}

// ehhh
void reverse(size_t i, size_t len, char s[]) {
  if (i < len / 2) {
    char temp = s[i];
    s[i] = s[len - i - 1];
    s[len - i - 1] = temp;
    reverse(i + 1, len, s);
  }
}
