#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
  enum { LOWER = 1, UPPER = 2 };
  int option = 0, c;
  if (argc == 2 && strcasecmp(argv[1], "-u") == 0)
    option |= UPPER;
  else
    option |= LOWER;

  while ((c = getchar()) != EOF)
    if (option & UPPER)
      putchar(toupper(c));
    else
      putchar(tolower(c));

  return 0;
}
