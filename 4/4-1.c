#include <stdio.h>

int strindex(char source[], char searchfor[]);

/* find all lines matching pattern */
int main(void) {
  char line[] = "You're breakin' my balls.";
  char pattern[] = "re"; /* pattern to search for */
  printf("strindex(\"%s\", \"%s\"): %d\n", line, pattern, strindex(line, pattern));
  return 0;
}

/* strindex:  return the rightmost index of t in s, −1 if none */
int strindex(char s[], char t[]) {
  int i, j, k = 0, index = -1;

  for (i = 0; s[i] != '\0'; i++) {
    for (j = i, k = 0; t[k] != '\0' && s[j] == t[k]; j++, k++)
      ;
    if (k > 0 && t[k] == '\0')
      index = i;
  }
  return index;
}
