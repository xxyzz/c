#include <ctype.h>  // tolower
#include <stdio.h>  // getline
#include <stdlib.h> // atof
#include <string.h> // strcmp, strdup

#define MAXLINES 5000 /* max #lines to be sorted */
#define NUMERIC 1     /* numeric sort */
#define REVERSE 2     /* reverse sort */
#define FOLDCASE 4    /* fold case */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void swap(void *v[], int, int);
void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *),
              int flags);
void tolowers(char *s);
int numcmp(const char *, const char *);

/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines; /* number of input lines read */
  int options = 0;
  char *lineptr[MAXLINES]; /* pointers to text lines */

  for (int i = 1; i < argc; i++) {
    if (*argv[i] == '-') {
      char c;
      while ((c = *++argv[i]))
        switch (c) {
        case 'n':
          options |= NUMERIC;
          break;
        case 'r':
          options |= REVERSE;
          break;
        case 'f':
          options |= FOLDCASE;
          break;
        default:
          break;
        }
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
    my_qsort((void **)lineptr, 0, nlines - 1,
             (int (*)(void *, void *))((options & NUMERIC) ? numcmp : strcmp),
             options);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

/* my_sort: sort v[left]...v[right] into increasing order */
void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *),
              int flags) {
  int i, last;

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    char *s1 = strdup(v[i]), *s2 = strdup(v[left]);
    if (flags & FOLDCASE) {
      tolowers(s1);
      tolowers(s2);
    }
    int reverse = flags & REVERSE;
    if (reverse && (*comp)(s1, s2) > 0)
      swap(v, ++last, i);
    else if (!reverse && (*comp)(s1, s2) < 0)
      swap(v, ++last, i);
    free(s1);
    free(s2);
  }
  swap(v, left, last);
  my_qsort(v, left, last - 1, comp, flags);
  my_qsort(v, last + 1, right, comp, flags);
}

/* convert a string to lower case */
void tolowers(char *s) {
  for (size_t i = 0; s[i]; i++)
    s[i] = (char)tolower(s[i]);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(const char *s1, const char *s2) {
  double v1, v2;

  v1 = atof(s1);
  v2 = atof(s2);
  if (v1 < v2)
    return -1;
  else if (v1 > v2)
    return 1;
  else
    return 0;
}

void swap(void *v[], int i, int j) {
  void *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
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
