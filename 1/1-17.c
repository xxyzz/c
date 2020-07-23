#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */
#define THRESHOLD 80

int my_getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print longest input line */
int main() {
  int len;               /* current line length */
  char line[MAXLINE];    /* current input line */

  while ((len = my_getline(line, MAXLINE)) > 0)
    if (len > THRESHOLD)
      printf("%s", line);
  return 0;
}

/* my_getline: read a line into s, return length */
int my_getline(char s[], int lim) {
  int c, i, j = 0;

  for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
    if (i < lim - 1) {
      s[i] = (char)c;
      ++j;
    }
  if (c == '\n') {
    s[j] = (char)c;
    ++i;
    ++j;
  }
  s[j] = '\0';
  return i;
}

/* copy: copy ′from′ into ′to′; assume to is big enough */
void copy(char to[], char from[]) {
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}
