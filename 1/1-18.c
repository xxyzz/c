#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int my_getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main() {
  int len;            /* current line length */
  char line[MAXLINE]; /* current input line */

  while ((len = my_getline(line, MAXLINE)) > 0)
    printf("length: %d, %s", len, line);
  return 0;
}

/* my_getline: read a line into s, remove trailing blanks
 * and tabs, return length
 */
int my_getline(char s[], int lim) {
  int c = ' ', i, j = 0;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i) {
      s[i] = (char)c;
      if (c != ' ' && c != '\t')
        j = i;
  }

  if (j == 0)
    return 0;
  if (c == '\n')
    s[++j] = (char)c;
  s[++j] = '\0';
  return j;
}

/* copy: copy ′from′ into ′to′; assume to is big enough */
void copy(char to[], char from[]) {
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
