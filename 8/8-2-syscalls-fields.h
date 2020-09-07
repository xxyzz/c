#define MYNULL 0
#define MYEOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */
#define ONE_MILLION 1000000

typedef struct _flag {
  int READ;    /* file open for reading */
  int WRITE;   /* file open for writing */
  int UNBUF;   /* file is unbuffered */
  int EOFFLAG; /* EOF has occurred on this file */
  int ERR;     /* error occurred on this file */
} Flag;

typedef struct _iobuf {
  char *ptr;  /* next character position */
  char *base; /* location of buffer */
  Flag flag;  /* mode of file access */
  int cnt;    /* characters left */
  int fd;     /* file descriptor */
} MYFILE;
extern MYFILE _iob[OPEN_MAX];

#define my_stdin (&_iob[0])
#define my_stdout (&_iob[1])
#define my_stderr (&_iob[2])

int _my_fillbuf(MYFILE *);
/* int _my_flushbuf(int, MYFILE *); */

#define my_feof(p) ((p)->flag.EOFGLAG)
#define my_ferror(p) ((p)->flag.ERR)
#define my_fileno(p) ((p)->fd)

#define my_getc(p) (--(p)->cnt >= 0 ? (int)*(p)->ptr++ : _my_fillbuf(p))

/* #define my_putc(x, p) (--(p)->cnt >= 0 ? *(p)->ptr++ = (x) :
 * _my_flushbuf((x), p)) */

#define my_getchar() my_getc(my_stdin)
/* #define my_putchar(x) my_putc((x), my_stdout) */
