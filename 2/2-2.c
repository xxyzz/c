#include <stdio.h>
#define LIMIT 10

int my_getline(char s[], int lim);

int main() {
  int len;
  char line[LIMIT];
  while ((len = my_getline(line, LIMIT)) > 0)
    printf("%s\n", line);

  return 0;
}

int my_getline(char s[], int lim) {
  int c = ' ', i;

  for (i = 0; i < lim - 1; ++i) {
    if ((c = getchar()) != EOF)
      if (c != '\n')
        s[i] = (char)c;
      else
        break;
    else
      break;
  }
  if (i < lim - 1 && c == '\n') {
    s[i] = '\n';
    ++i;
  }
  s[i] = '\0';
  return i;
}
