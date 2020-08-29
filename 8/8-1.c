#include <stdio.h>
#ifdef Darwin
#include <sys/types.h>
#include <sys/uio.h>
#endif
#include <fcntl.h>    // open
#include <stdlib.h>   // exit
#include <sys/time.h> // gettimeofday
#include <unistd.h>   // read, write, close

#define ONE_MILLION 1000000

void filecopy(int, int);

int main(int argc, char *argv[]) {
  int in;
  char *prog = argv[0]; /* program name for errors */
  struct timeval start, end;
  gettimeofday(&start, NULL);

  if (argc == 1) /* no args; copy standard input */
    filecopy(STDIN_FILENO, STDOUT_FILENO);
  else
    while (--argc > 0)
      if ((in = open(*++argv, O_RDONLY)) <= 0) {
        fprintf(stderr, "%s: can′t open %s\n", prog, *argv);
        exit(EXIT_FAILURE);
      } else {
        filecopy(in, STDOUT_FILENO);
        close(in);
      }
  gettimeofday(&end, NULL);
  long long startusec, endusec;
  startusec = start.tv_sec * ONE_MILLION + start.tv_usec;
  endusec = end.tv_sec * ONE_MILLION + end.tv_usec;
  printf("Time (seconds): %f\n", ((double)(endusec - startusec) / ONE_MILLION));
  return 0;
}

/* filecopy: copy file in to file out */
void filecopy(int in, int out) {
  int c;

  while (read(in, &c, 1) == 1)
    write(out, &c, 1);
}
