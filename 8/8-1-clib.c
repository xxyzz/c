#include <stdio.h>  // getc, putc
#include <stdlib.h> // exit
#include <sys/time.h> // gettimeofday

#define ONE_MILLION 1000000

void filecopy(FILE *, FILE *);

int main(int argc, char *argv[]) {
  FILE *fp;
  char *prog = argv[0]; /* program name for errors */
  struct timeval start, end;
  gettimeofday(&start, NULL);

  if (argc == 1) /* no args; copy standard input */
    filecopy(stdin, stdout);
  else
    while (--argc > 0)
      if ((fp = fopen(*++argv, "r")) == NULL) {
        fprintf(stderr, "%s: can′t open %s\n", prog, *argv);
        exit(EXIT_FAILURE);
      } else {
        filecopy(fp, stdout);
        fclose(fp);
      }
  if (ferror(stdout)) {
    fprintf(stderr, "%s: error writing stdout\n", prog);
    exit(EXIT_FAILURE);
  }
  gettimeofday(&end, NULL);
  long long startusec, endusec;
  startusec = start.tv_sec * ONE_MILLION + start.tv_usec;
  endusec = end.tv_sec * ONE_MILLION + end.tv_usec;
  printf("Time (seconds): %f\n", ((double)(endusec - startusec) / ONE_MILLION));
  return 0;
}

/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp) {
  int c;

  while ((c = getc(ifp)) != EOF)
    putc(c, ofp);
}

/*
 * $ ./8-1.out ./8-1.c
 * $ ./8-1-clib.out ./8-1.c
 * system      call: 0.002580 seconds
 * library function: 0.000328 seconds
 * oh boy
 */
