#include <stdio.h>  // getline
#include <stdlib.h> // free
#include <string.h> // strcpy

#define MAXLINES 50 /* max #lines to be sorted */
#define MAXLEN 100   /* max length of any input line */

static char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *linep[], int nlines, char *bfa);
void writelines(char *linep[], int nlines);

int main() {
  char bfa[MAXLINES * MAXLINES];
  int lines = readlines(lineptr, MAXLINES, bfa);
  writelines(lineptr, lines);
  return 0;
}

/* readlines: read input lines */
int readlines(char *linep[], int maxlines, char *bfa) {
  int nlines = 0;
  char *p = bfa, *line = NULL;
  size_t len = 0;
  ssize_t nread = 0;

  while ((nread = getline(&line, &len, stdin)) > 0) {
    if (nlines >= maxlines || nread > MAXLEN ||
        p + nread > bfa + MAXLINES * MAXLEN)
      return -1;
    else {
      line[nread - 1] = '\0'; /* delete newline */
      strcpy(p, line);
      linep[nlines++] = p;
      p += nread;
    }
  }
  free(line);
  return nlines;
}

/* writelines: write output lines */
void writelines(char *linep[], int nlines) {
  while(nlines-- > 0)
    printf("%s\n", *linep++);
}
