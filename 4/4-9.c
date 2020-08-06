#include <stdio.h>

/*
 * 0xFFFF             0xFF
 * ungetch EOF(-1) -> signed char -> getch int(-1) 0xFFFF
 * ungetch EOF(-1) -> unsigned char -> getch int(255) 0x00FF
 *
 * declare buf as int[]
 */

int main(void) {
  printf("signed char: %d\n", (int)((signed char)EOF));
  printf("unsigned char: %d\n", (int)((unsigned char)EOF));
  printf("char: %d\n", (int)((char)EOF));
  return 0;
}
