#include <stdio.h>  // printf, fprintf, fopen, fclose
#include <stdlib.h> // exit
#include <sys/ioctl.h>
#include <unistd.h> // STDOUT_FILENO

int main(int argc, char *argv[]) {
  if (argc == 1)
    return 0;

  size_t linenum = 0;
  int terminal_rows;
  struct winsize wz;
  FILE *f;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;

  if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &wz) == -1) {
    fprintf(stderr, "itoctl failed.\n");
    exit(EXIT_FAILURE);
  }
  terminal_rows = wz.ws_row;

  for (int i = 1; i < argc; i++) {
    if ((f = fopen(argv[i], "r")) == NULL) {
      fprintf(stderr, "Can't open %s\n", argv[i]);
      exit(EXIT_FAILURE);
    }

    // print new lines to start at new page
    if (linenum > 0) {
      int blanks = terminal_rows - (int)(linenum + 1) % terminal_rows;
      while (blanks-- > 0)
        printf("\n");
    }

    linenum = 0;
    printf("%s\n", argv[i]); // filename
    while ((nread = getline(&line, &len, f)) != -1)
      printf("%ld: %s", ++linenum, line);

    fclose(f);
  }
  free(line);

  return 0;
}
