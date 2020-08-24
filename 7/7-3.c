#include <ctype.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#define FMTLEN 1024

void minprintf(char *, ...);

int main() {
  minprintf("%d\n", 42);
  minprintf("%d %d\n", 42, 24);
  minprintf("%5g\n", 0.0000000000042);
  minprintf(":%-10.3d:\n", 42);
  minprintf("%s\n", "If you make money from war, you're scum. If you can't "
                    "make money from bounty hunting, you're an idiot!");
  minprintf(
      "%% %s\n",
      "What are you so afraid of? You act like a scared little fox-squirrel.");
  return 0;
}

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...) {
  va_list ap; /* points to each unnamed arg in turn */
  char *p, *fmts;
  if ((fmts = malloc(FMTLEN)) == NULL)
    return;
  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for (p = fmt; *p; p++) {
    if (*p != '%') {
      putchar(*p);
      continue;
    }

    int len = 0;
    fmts[len++] = '%';
    while ((isnumber(*(p + 1)) || *(p + 1) == '.' || *(p + 1) == '-') && len < FMTLEN)
      fmts[len++] = *++p;
    fmts[len++] = *(p + 1);
    fmts[len] = '\0';

    switch (*++p) {
    case 'd':
    case 'i':
    case 'o':
    case 'x':
    case 'X':
    case 'u':
    case 'c':
      printf(fmts, va_arg(ap, int));
      break;
    case 's':
      printf(fmts, va_arg(ap, char *));
      break;
    case 'f':
    case 'e':
    case 'E':
    case 'g':
    case 'G':
      printf(fmts, va_arg(ap, double));
      break;
    case 'p':
      printf(fmts, va_arg(ap, void *));
      break;
    case '%':
      putchar('%');
      break;
    default:
      putchar(*p);
      break;
    }
  }
  va_end(ap); /* clean up when done */
  free(fmts);
}
