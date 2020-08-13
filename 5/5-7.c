#include <stdio.h>  // getline
#include <stdlib.h> // free
#include <string.h> // strcpy

#define MAXLINES 50 /* max #lines to be sorted */

int readlines(char *linep[], int nlines);
void writelines(char *linep[], int nlines);

int main() {
  char *lineptr[MAXLINES]; /* pointers to text lines */
  int lines = readlines(lineptr, MAXLINES);
  writelines(lineptr, lines);
  return 0;
}

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines) {
  int nlines = 0;
  char *line = NULL;
  size_t len = 0;
  ssize_t nread = 0;

  while ((nread = getline(&line, &len, stdin)) > 0) {
    if (nlines >= maxlines)
      return -1;
    else {
      line[nread - 1] = '\0'; /* delete newline */
      lineptr[nlines++] = strdup(line);
    }
  }
  free(line);
  return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines) {
  while (nlines-- > 0) {
    printf("%s\n", *lineptr);
    free(*lineptr++);
  }
}
