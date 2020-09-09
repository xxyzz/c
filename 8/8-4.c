#include "8-3-syscalls.h"
#include <fcntl.h> /* open */
#include <stdio.h>
#include <stdlib.h> /* malloc, free */
#include <unistd.h> /* lseek, write, close */
#define PERMS 0666  /* RW for owner, group, others */

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
  bufsize = (fp->flag & _UNBUF) ? 1 : MYBUFSIZ;
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

/* _my_flushbuf: allocate and fill output buffer */
int _my_flushbuf(int c, MYFILE *fp) {
  size_t bufsize;
  int first_character = 0;
  if ((fp->flag & (_WRITE | _EOF | _ERR)) != _WRITE)
    return EOF;
  bufsize = (fp->flag & _UNBUF) ? 1 : MYBUFSIZ;
  if (fp->base == NULL) { /* no buffer yet */
    if ((fp->base = (char *)malloc(bufsize)) == NULL)
      return EOF; /* can′t get buffer */
    first_character = 1;
  }
  fp->ptr = fp->base;
  if (fp->cnt == -1 && !first_character) {
    if (write(fp->fd, fp->base, bufsize) != (ssize_t)bufsize)
      return EOF;
  }
  *fp->ptr++ = (char)c;
  fp->cnt = (int)bufsize - 1;
  return c;
}

int my_fflush(MYFILE *fp) {
  if (fp == NULL || fp->base == NULL)
    return -1;
  if ((fp->flag & _WRITE) != _WRITE || fp->base == NULL)
    return -1;
  int bufsize = (fp->flag & _UNBUF) ? 1 : MYBUFSIZ;
  int len = fp->cnt == 0 ? bufsize : bufsize - fp->cnt;
  if (write(fp->fd, fp->base, (size_t)len) != (ssize_t)len)
    return -1;
  fp->cnt = 0;
  return 0;
}

int my_fclose(MYFILE *fp) {
  if (fp == NULL)
    return -1;
  if (fp->flag & _WRITE)
    my_fflush(fp);
  if (fp->base != NULL)
    free(fp->base);
  fp->flag = 0;
  fp->base = NULL;
  if (close(fp->fd) == -1)
    return -1;
  return 0;
}

int my_fseek(MYFILE *fp, long offset, int whence) {
  if (fp == NULL || !(fp->flag & (_WRITE | _READ)))
    return -1;
  if (fp->flag & _WRITE && fp->base != NULL)
    if (my_fflush(fp) == -1) {
      fp->flag |= _ERR;
      return -1;
    }
  if (fp->flag & _READ) {
    fp->cnt = 0;
    fp->ptr = fp->base;
  }
  if (lseek(fp->fd, offset, whence) == -1) {
    fp->flag |= _ERR;
    return -1;
  }
  return 0;
}

MYFILE _iob[OPEN_MAX] = {/* stdin, stdout, stderr: */
                         {0, (char *)0, (char *)0, _READ, 0},
                         {0, (char *)0, (char *)0, _WRITE, 1},
                         {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

int main(int argc, char *argv[]) {
  MYFILE *fp = my_stdin;
  int c;

  if (argc > 1)
    if ((fp = my_fopen(argv[1], "r")) == NULL) {
      fprintf(stderr, "What's wrong with you?\n");
      exit(EXIT_FAILURE);
    }

  my_fseek(fp, 10, SEEK_CUR);

  while ((c = my_getc(fp)) != EOF)
    my_putchar((char)c);

  my_fclose(fp);
  my_fclose(my_stdout);

  return 0;
}
