#include <ctype.h>  // tolower, isalnum, isblank
#include <stdio.h>  // getline
#include <stdlib.h> // atoi, atof, exit
#include <string.h> // strcmp, strdup, strsep
#include <unistd.h> // getopt

#define MAXLINES 5000 /* max #lines to be sorted */
#define NUMERIC 1     /* numeric sort */
#define REVERSE 2     /* reverse sort */
#define FOLDCASE 4    /* fold case */
#define DIRECTORY 8   /* compare only on letters, numbers and blanks */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines, int flags);
void swap(void *v[], int, int);
void my_qsort(void *lineptr[], int left, int right, int (*comp)(void *, void *),
              int flags, int field);
void tolowers(char *s);
void filterstring(char *s);
int numcmp(const char *, const char *);
void getfield(char **s, int field);

/* sort input lines */
int main(int argc, char *argv[]) {
  int nlines; /* number of input lines read */
  int options = 0;
  int fields[3] = {-1};
  int opt;
  char *lineptr[MAXLINES]; /* pointers to text lines */

  while ((opt = getopt(argc, argv, "n:rf:d:")) != -1) {
    switch (opt) {
    case 'n':
      options |= NUMERIC;
      fields[0] = atoi(optarg);
      break;
    case 'r':
      options |= REVERSE;
      break;
    case 'f':
      options |= FOLDCASE;
      fields[1] = atoi(optarg);
      break;
    case 'd':
      options |= DIRECTORY;
      fields[2] = atoi(optarg);
      break;
    default: /* '?' */
      fprintf(stderr, "Usage: %s [-n field] [-r field] [-f field] [-d field]\n",
              argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  if ((nlines = readlines(lineptr, MAXLINES)) > 0) {
    if (options & NUMERIC)
      my_qsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))numcmp,
               NUMERIC, fields[0]);
    if (options & FOLDCASE)
      my_qsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))strcmp,
               FOLDCASE, fields[1]);
    if (options & DIRECTORY)
      my_qsort((void **)lineptr, 0, nlines - 1, (int (*)(void *, void *))strcmp,
               DIRECTORY, fields[2]);
    writelines(lineptr, nlines, options);
    return 0;
  } else {
    printf("input too big to sort\n");
    return 1;
  }
}

/* my_sort: sort v[left]...v[right] into increasing order */
void my_qsort(void *v[], int left, int right, int (*comp)(void *, void *),
              int flags, int field) {
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
    } else if (flags & DIRECTORY) {
      filterstring(s1);
      filterstring(s2);
    }
    if (field != -1) {
      getfield(&s1, field);
      getfield(&s2, field);
    }
    if ((*comp)(s1, s2) < 0)
      swap(v, ++last, i);
    free(s1);
    free(s2);
  }
  swap(v, left, last);
  my_qsort(v, left, last - 1, comp, flags, field);
  my_qsort(v, last + 1, right, comp, flags, field);
}

void getfield(char **s, int field) {
  int i = 0;
  char *token;
  while ((token = strsep(s, "-")) != NULL) {
    if (i++ == field) {
      *s = strdup(token);
      break;
    }
  }
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
    if (isalnum(s[i]) || isblank(s[i]))
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
void writelines(char *lineptr[], int nlines, int flags) {
  while (nlines-- > 0) {
    if (flags & REVERSE) {
      char *p = *(lineptr + nlines);
      printf("%s\n", p);
      free(p);
    } else {
      printf("%s\n", *lineptr);
      free(*lineptr++);
    }
  }
}
