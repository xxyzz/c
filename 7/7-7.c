#include <stdio.h>
#include <stdlib.h>       // exit
#include <string.h>       // strsep
#include <sys/resource.h> //RLIMIT_NOFILE
#include <unistd.h>       // getopt

enum { EXCEPT = 1, NUMBER = 2, FROMFILE = 4 };

void search_pattern(FILE *, char *, int);

int main(int argc, char *argv[]) {
  int opt, flags = 0;
  size_t filenum = 0;
  char *token, *pattern = NULL;
  FILE *files[RLIMIT_NOFILE];
  while ((opt = getopt(argc, argv, "xnf:p:")) != -1) {
    switch (opt) {
    case 'x':
      flags |= EXCEPT;
      break;
    case 'n':
      flags |= NUMBER;
      break;
    case 'f':
      flags |= FROMFILE;
      while ((token = strsep(&optarg, ",")) != NULL)
        if ((files[filenum++] = fopen(token, "r")) == NULL) {
          fprintf(stderr, "Can't open %s\n", token);
          exit(EXIT_FAILURE);
        }
      break;
    case 'p':
      if ((pattern = strdup(optarg)) == NULL) {
        fprintf(stderr, "strdup failed, jeez.\n");
        exit(EXIT_FAILURE);
      }
      break;
    default:
      fprintf(stderr,
              "Usage: %s [-x] [-n] [-p <pattern>] [-f <file1>,<file2>...]",
              argv[0]);
      exit(EXIT_FAILURE);
    }
  }

  if (pattern == NULL) {
    fprintf(stderr, "Where's the goddamn pattern?\n");
    exit(EXIT_FAILURE);
  }

  if (flags & FROMFILE)
    for (size_t i = 0; i < filenum; i++)
      search_pattern(files[i], pattern, flags);
  else
    search_pattern(stdin, pattern, flags);

  return 0;
}

void search_pattern(FILE *f, char *pattern, int flags) {
  char *line = NULL;
  size_t len = 0;
  ssize_t nread;
  size_t lineno = 0;

  while ((nread = getline(&line, &len, f)) != -1) {
    lineno++;
    if ((strstr(line, pattern) != NULL) != (flags & EXCEPT)) {
      if (flags & NUMBER)
        printf("%ld: ", lineno);
      printf("%s", line);
    }
  }
}
