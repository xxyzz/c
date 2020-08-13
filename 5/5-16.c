#include <ctype.h>  // tolower, isdigit, isalpha, isblank
#include <stdio.h>  // getline
#include <stdlib.h> // atof
#include <string.h> // strcmp, strdup

#define MAXLINES 5000 /* max #lines to be sorted */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void swap(void *v[], int, int);
void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *),
              int reverse, int foldcase, int directory);
void tolowers(char *s);
void filterstring(char *s);
int numcmp(const char *, const char *);

/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines;       /* number of input lines read */
  int numeric = 0;  /* 1 if numeric sort */
  int reverse = 0;  /* 1 if reverse sort */
  int foldcase = 0; /* 1 if fold case  */
  int directory_order =
      0; /* 1 if compare only on letters, numbers and blanks */
  char *lineptr[MAXLINES]; /* pointers to text lines */

  for (int i = 1; i < argc; i++) {
    if (*argv[i] == '-') {
      char c;
      while ((c = *++argv[i]))
        switch (c) {
        case 'n':
          numeric = 1;
          break;
        case 'r':
          reverse = 1;
          break;
        case 'f':
          foldcase = 1;
          break;
        case 'd':
          directory_order = 1;
          break;
        default:
          break;
        }
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
    my_qsort((void **)lineptr, 0, nlines - 1,
             (int (*)(void *, void *))(numeric ? numcmp : strcmp), reverse,
             foldcase, directory_order);
    writelines(lineptr, nlines);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

/* my_sort: sort v[left]...v[right] into increasing order */
void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *),
              int reverse, int foldcase, int directory) {
  int i, last;

  if (left >= right) /* do nothing if array contains */
    return;          /* fewer than two elements */
  swap(v, left, (left + right) / 2);
  last = left;
  for (i = left + 1; i <= right; i++) {
    char *s1 = strdup(v[i]), *s2 = strdup(v[left]);
    if (foldcase) {
      tolowers(s1);
      tolowers(s2);
    }
    if (directory) {
      filterstring(s1);
      filterstring(s2);
    }
    if (reverse && (*comp)(s1, s2) > 0)
      swap(v, ++last, i);
    else if (!reverse && (*comp)(s1, s2) < 0)
      swap(v, ++last, i);
    free(s1);
    free(s2);
  }
  swap(v, left, last);
  my_qsort(v, left, last - 1, comp, reverse, foldcase, directory);
  my_qsort(v, last + 1, right, comp, reverse, foldcase, directory);
}

/* convert a string to lower case */
void tolowers(char *s) {
  for (size_t i = 0; s[i]; i++)
    s[i] = (char)tolower(s[i]);
}

/* remove characters that are not letters, numbers or blanks */
void filterstring(char *s) {
  size_t j = 0;
  for (size_t i = 0; s[i]; i++)
    if (isalpha(s[i]) || isdigit(s[i]) || isblank(s[i]))
      s[j++] = s[i];
  s[j] = '\0';
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
