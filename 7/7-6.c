#include <stdio.h>
#include <stdlib.h> // exit
#include <string.h>

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Go kill yourself.");
    exit(EXIT_FAILURE);
  }
  FILE *f1, *f2;
  if ((f1 = fopen(argv[1], "r")) == NULL) {
    fprintf(stderr, "can't open %s, moron.", argv[1]);
    exit(EXIT_FAILURE);
  }
  if ((f2 = fopen(argv[2], "r")) == NULL) {
    fprintf(stderr, "can't open %s, douchebag.", argv[2]);
    exit(EXIT_FAILURE);
  }

  char *line1 = NULL, *line2 = NULL;
  size_t len1 = 0, len2 = 0, linenum = 0;
  ssize_t nread1, nread2;

  do {
    nread1 = getline(&line1, &len1, f1);
    nread2 = getline(&line2, &len2, f2);
    linenum++;
  } while (nread1 != -1 && nread2 != -1 && strcmp(line1, line2) == 0);

  if (nread1 > 0)
    printf("%s line %zu: %s", argv[1], linenum, line1);
  if (nread2 > 0)
    printf("%s line %zu: %s", argv[2], linenum, line2);

  free(line1);
  free(line2);
  fclose(f1);
  fclose(f2);
  return 0;
}
