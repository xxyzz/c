#include <stdio.h>

void strcaat(char *s, char *t);

int main() {
  char s[1000] = "Who is Eric Cartman's mother? ";
  char *t = "Is it Ms. Crabtree, Sheila Broflovski, the Mayor?";
  strcaat(s, t);
  printf("%s\n", s);
  return 0;
}

/* strcaat: concatenate t to end of s; s must be big enough */
void strcaat(char *s, char *t) {
  while (*s) /* find end of s */
    s++;
  while ((*s++ = *t++)) /* copy t */
    ;
}
