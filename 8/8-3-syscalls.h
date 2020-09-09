#define MYNULL 0
#define MYEOF (-1)
#define MYBUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

typedef struct _iobuf {
  int cnt;    /* characters left */
  char *ptr;  /* next character position */
  char *base; /* location of buffer */
  int flag;   /* mode of file access */
  int fd;     /* file descriptor */
} MYFILE;
extern MYFILE _iob[OPEN_MAX];

#define my_stdin (&_iob[0])
#define my_stdout (&_iob[1])
#define my_stderr (&_iob[2])

enum _flags {
  _READ = 01,  /* file open for reading */
  _WRITE = 02, /* file open for writing */
  _UNBUF = 04, /* file is unbuffered */
  _EOF = 010,  /* EOF has occurred on this file */
  _ERR = 020   /* error occurred on this file */
};

int _my_fillbuf(MYFILE *);
int _my_flushbuf(int, MYFILE *);

#define my_feof(p) (((p)->flag & _EOF) != 0)
#define my_ferror(p) (((p)->flag & _ERR) != 0)
#define my_fileno(p) ((p)->fd)

#define my_getc(p) (--(p)->cnt >= 0 ? (int)*(p)->ptr++ : _my_fillbuf(p))

#define my_putc(x, p)                                                          \
  (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _my_flushbuf((x), p))

#define my_getchar() my_getc(my_stdin)
#define my_putchar(x) my_putc((x), my_stdout)

int my_fflush(MYFILE *);
int my_fclose(MYFILE *);
int my_fseek(MYFILE *, long, int);
