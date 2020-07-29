#include <stdio.h>  // getline
#include <ctype.h>  // tolower, isdigit
#include <stdlib.h> // free

int htoi(char s[]);

int main() {
  char *s = NULL;
  size_t len = 100;
  while (getline(&s, &len, stdin) != -1)
    printf("%d\n", htoi(s));
  free(s);
  return 0;
}

int htoi(char s[]) {
  int result = 0, i;
  if (s[0] == '0' && tolower(s[1]) == 'x') {
    for (i = 2; s[i] != '\n' && s[i] != '\0'; i++) {
      result = result * 16;
      if (isdigit(s[i]))
        result += s[i] - '0';
      else
        result += tolower(s[i]) - 'a' + 10;
    }
  }

  return result;
}
