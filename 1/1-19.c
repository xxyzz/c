#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int my_getline(char line[], int maxline);
void copy(char to[], char from[]);
char *reverse(char s[]);

/* print longest input line */
int main() {
  int len;            /* current line length */
  char line[MAXLINE]; /* current input line */

  while ((len = my_getline(line, MAXLINE)) > 0)
    printf("%s", reverse(line));
  return 0;
}

/* my_getline: read a line into s, return length */
int my_getline(char s[], int lim) {
  int c = ' ', i;

  for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    s[i] = (char)c;
  if (c == '\n') {
    s[i] = (char)c;
    ++i;
  }
  s[i] = '\0';
  return i;
}

/* copy: copy ′from′ into ′to′; assume to is big enough */
void copy(char to[], char from[]) {
  int i;

  i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}

char *reverse(char s[]) {
  int i = 0, j = 0;
  while (s[i] != '\0')
    ++i;
  --i; // rm \0
  if (s[i] == '\n')
    --i; // rm \n
  while (j < i) {
    char temp = s[j];
    s[j] = s[i];
    s[i] = temp;
    --i;
    ++j;
  }
  return s;
}
