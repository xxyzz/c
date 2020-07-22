#include <stdio.h>

#define IN 1  /* inside a word */
#define OUT 0 /* outside a word */
#define MAX_LENGTH 10

/* print histogram of the lengths of words in input. */
int main() {
  int c, state = OUT, l = 0;
  int nlength[MAX_LENGTH];

  for (int i = 0; i < MAX_LENGTH; ++i)
    nlength[i] = 0;

  while ((c = getchar()) != EOF)
    if (c == ' ' || c == '\n' || c == '\t') {
      if (state == IN) {
        state = OUT; // end
        if (l < MAX_LENGTH)
          ++nlength[l - 1];
        else
          ++nlength[MAX_LENGTH - 1];
      }
    } else if (state == OUT) {
      state = IN;
      l = 1; // begin
    } else
      ++l; // inside

  for (int i = 0; i < MAX_LENGTH; ++i) {
    if (i != MAX_LENGTH - 1)
      printf("%d: ", i + 1);
    else
      printf("10+: ");

    for (int j = 0; j < nlength[i]; j++)
      printf("*");
    printf("\n");
  }
}
