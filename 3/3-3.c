#include <ctype.h>  // isdigit, isalpha
#include <stdio.h>

void expand(char s1[], char s2[]);

int main() {
  char s2[100];
  expand("a-b-c", s2);
  printf("expand(\"a-b-c\",s2): %s\n", s2);
  expand("a-z0-9", s2);
  printf("expand(\"a-z0−9\",s2): %s\n", s2);
  expand("-a-z", s2);
  printf("expand(\"-a-z\",s2): %s\n", s2);
  return 0;
}

void expand(char s1[], char s2[]) {
  int i = 0, j = 0;
  char c;
  while((c = s1[i++]) != '\0') {
    if (s1[i] == '-' &&
        ((isdigit(c) && isdigit(s1[i + 1])) ||
         (isalpha(c) && isalpha(s1[i + 1]))) &&
        c <= s1[i + 1]) {
      while (c < s1[i + 1])
        s2[j++] = c++;
      i++;
    } else
      s2[j++] = c;
  }
  s2[j] = '\0';
}
