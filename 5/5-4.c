#include <stdio.h>

int strend(char *, char *);

int main() {
  char *s =
      "What is with all the questions? Cos I'm interested. Why? Cos I have the "
      "insatiable curiosity of the young. Why? All right. Truce.";
  char *t = "All right. Truce.";
  char *u = "But I've got something you haven't... this small piece of coal.";
  printf("at end: %d\n", strend(s, t));
  printf("not at end: %d\n", strend(s, u));
  return 0;
}

int strend(char *s, char *t) {
  char *t_cp = t;
  while (*s)
    s++;
  while (*t_cp)
    t_cp++;
  while (*s == *t_cp) {
    if (t_cp == t)
      return 1;
    s--;
    t_cp--;
  }
  return 0;
}
