#include <stdio.h>

void squeeze(char s1[], char s2[]);

int main() {
  char s1[] = "Screw you guys, I'm going home!";
  char s2[] = "I'll kick you in the nuts!";
  squeeze(s1, s2);
  printf("%s\n", s1);
  return 0;
}

void squeeze(char s1[], char s2[]) {
  int i, j, k;
  for (i = k = 0; s1[i] != '\0' ; i++) {
    for (j = 0; s2[j] != '\0' && s1[i] != s2[j]; j++)
      ;
    if (s2[j] == '\0') // s2 doesn't contain s1[i]
      s1[k++] = s1[i];
  }
  s1[k] = '\0';
}
