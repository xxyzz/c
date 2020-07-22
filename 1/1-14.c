#include <stdio.h>
#include <ctype.h> // tolower

#define CHAEACTERS 26

/* print histogram of the frequencies of different characters in input. */
int main() {
  int c, freqencies[CHAEACTERS];

  for (int i = 0; i < CHAEACTERS; ++i)
    freqencies[i] = 0;

  while ((c = getchar()) != EOF) {
    c = tolower(c);
    if (c >= 'a' && c <= 'z')
      ++freqencies[c - 'a'];
  }

  for (int i = 0; i < CHAEACTERS; ++i) {
    printf("%c: ", i + 'a');
    for (int j = 0; j < freqencies[i]; j++)
      printf("*");
    printf("\n");
  }
}
