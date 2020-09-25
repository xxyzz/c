#include "fsize.h"
#include "dirent.h"
#include <dirent.h>    /* opendir, readdir, closedir */
#include <grp.h>       /* getgrgid */
#include <pwd.h>       /* getpwuid */
#include <stdio.h>     /* sprintf, fprintf */
#include <string.h>    /* strcmp, strlen */
#include <sys/stat.h>  /* structure returned by stat, st_mode flags */
#include <sys/types.h> /* typedefs: dev_t, ino_t */
#include <time.h>      /* localtime, strftime  */
#include <unistd.h>

/* fsize: print size of file "name" */
void fsize(char *name) {
  struct stat stbuf;
  struct tm *tmp;
  struct passwd *up;
  struct group *gp;
  char last_access[200];

  if (stat(name, &stbuf) == -1) {
    fprintf(stderr, "fsize: can′t access %s\n", name);
    return;
  }
  if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
    dirwalk(name, fsize);
  if ((tmp = localtime(&stbuf.st_atime)) == NULL) {
    fprintf(stderr, "localtime failed\n");
    return;
  }
  if (strftime(last_access, sizeof(last_access), "%c", tmp) == 0) {
    fprintf(stderr, "strftime returned 0\n");
    return;
  }
  if ((up = getpwuid(stbuf.st_uid)) == NULL) {
    fprintf(stderr, "not found uid: %d\n", stbuf.st_uid);
    return;
  }
  if ((gp = getgrgid(stbuf.st_gid)) == NULL) {
    fprintf(stderr, "not found gid: %d\n", stbuf.st_gid);
    return;
  }
  printf("%4d %5s %5s %8lld %s %s\n", stbuf.st_nlink, up->pw_name, gp->gr_name,
         stbuf.st_size, last_access, name);
}

/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *)) {
  char name[MAX_PATH];
  struct dirent *dp;
  DIR *dfd;

  if ((dfd = opendir(dir)) == NULL) {
    fprintf(stderr, "dirwalk: can′t open %s\n", dir);
    return;
  }
  while ((dp = readdir(dfd)) != NULL) {
    if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0)
      continue; /* skip self and parent */
    if (strlen(dir) + strlen(dp->d_name) + 2 > sizeof(name))
      fprintf(stderr, "dirwalk: name %s/%s too long\n", dir, dp->d_name);
    else {
      sprintf(name, "%s/%s", dir, dp->d_name);
      (*fcn)(name);
    }
  }
  closedir(dfd);
}
