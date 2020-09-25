#include "fsize.h"

/* print file sizes */
int main(int argc, char *argv[]) {
  if (argc == 1) /* default: current directory */
    fsize(".");
  else
    while (--argc > 0)
      fsize(*++argv);
  return 0;
}
