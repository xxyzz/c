#include "8-2-syscalls.h"
#include <fcntl.h> /* open */
#include <stdio.h>
#include <stdlib.h>   /* malloc, free */
#include <sys/time.h> /* gettimeofday */
#include <unistd.h>   /* lseek, write */
#define PERMS 0666    /* RW for owner, group, others */

/* fopen: open file, return file ptr */
static MYFILE *my_fopen(char *name, char *mode) {
  int fd;
  MYFILE *fp;

  if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    return NULL;
  for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    if ((fp->flag & (_READ | _WRITE)) == 0)
      break;                 /* found free slot */
  if (fp >= _iob + OPEN_MAX) /* no free slots */
    return NULL;

  if (*mode == 'w')
    fd = creat(name, PERMS);
  else if (*mode == 'a') {
    if ((fd = open(name, O_WRONLY, 0)) == -1)
      fd = creat(name, PERMS);
    lseek(fd, 0L, 2);
  } else
    fd = open(name, O_RDONLY, 0);
  if (fd == -1) /* couldn′t access name */
    return NULL;
  fp->fd = fd;
  fp->cnt = 0;
  fp->base = NULL;
  fp->flag = (*mode == 'r') ? _READ : _WRITE;
  return fp;
}

/* _my_fillbuf: allocate and fill input buffer */
int _my_fillbuf(MYFILE *fp) {
  size_t bufsize;

  if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
  if (fp->base == NULL) /* no buffer yet */
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
      return EOF; /* can′t get buffer */
  fp->ptr = fp->base;
  fp->cnt = (int)read(fp->fd, fp->ptr, bufsize);
  if (--fp->cnt < 0) {
    if (fp->cnt == -1)
      fp->flag |= _EOF;
    else
      fp->flag |= _ERR;
    fp->cnt = 0;
    return EOF;
  }
  return (unsigned char)*fp->ptr++;
}

MYFILE _iob[OPEN_MAX] = {/* stdin, stdout, stderr: */
                         {0, (char *)0, (char *)0, _READ, 0},
                         {0, (char *)0, (char *)0, _WRITE, 1},
                         {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

int main(int argc, char *argv[]) {
  MYFILE *fp = my_stdin;
  int c;
  struct timeval start, end;
  gettimeofday(&start, NULL);

  if (argc > 1)
    if ((fp = my_fopen(argv[1], "r")) == NULL) {
      fprintf(stderr, "What's wrong with you?\n");
      exit(EXIT_FAILURE);
    }

  while ((c = my_getc(fp)) != EOF)
    putchar(c);

  gettimeofday(&end, NULL);
  long long startusec, endusec;
  startusec = start.tv_sec * ONE_MILLION + start.tv_usec;
  endusec = end.tv_sec * ONE_MILLION + end.tv_usec;

  printf("\nTime (seconds): %f\n",
         ((double)(endusec - startusec) / ONE_MILLION));

  if (fp->base != NULL)
    free(fp->base);

  return 0;
}
