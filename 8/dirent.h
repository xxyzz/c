#ifndef __MY_DIRENT_H__
#define __MY_DIRENT_H__
#define MY_NAME_MAX 14 /* longest filename component; */
                       /* system-dependent */
#define MYDIRSIZ 14

typedef struct {              /* portable directory entry: */
  long ino;                   /* inode number */
  char name[MY_NAME_MAX + 1]; /* name + ′\0′ terminator */
} MYDirent;

typedef struct { /* minimal DIR: no buffering, etc. */
  int fd;        /* file descriptor for directory */
  MYDirent d;    /* the directory entry */
} MYDIR;

MYDIR *myopendir(char *dirname);
MYDirent *myreaddir(MYDIR *dfd);
void myclosedir(MYDIR *dfd);
#endif
