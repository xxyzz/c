#include <stdarg.h> // va_arg
#include <stdio.h>  // scanf

#define FMTLEN 1024

int my_scanf(char *, ...);

int main() {
  int i;
  float f;
  char s[FMTLEN];
  my_scanf("%d", &i);
  printf("%d\n", i);
  my_scanf("%f", &f);
  printf("%f\n", f);
  my_scanf("%s", s);
  printf("%s\n", s);
  return 0; }

int my_scanf(char *fmt, ...) {
  va_list ap; /* points to each unnamed arg in turn */
  char *p, fmts[3];
  int result = 0;
  va_start(ap, fmt); /* make ap point to 1st unnamed arg */
  for (p = fmt; *p; p++) {
    if (*p != '%')
      continue;
    fmts[0] = '%';
    fmts[1] = *(p + 1);
    fmts[2] = '\0';
    switch (*++p) {
    case 'd':
    case 'i':
    case 'o':
    case 'x':
      result = scanf(fmts, va_arg(ap, int *));
      break;
    case 'u':
      result = scanf(fmts, va_arg(ap, unsigned int *));
      break;
    case 'c':
    case 's':
      result = scanf(fmts, va_arg(ap, char *));
      break;
    case 'e':
    case 'f':
    case 'g':
      result = scanf(fmts, va_arg(ap, double *));
      break;
    case 'p':
      result = scanf(fmts, va_arg(ap, void *));
      break;
    case '%':
      result = scanf("%%");
      break;
    default:
      break;
    }
  }
  va_end(ap); /* clean up when done */
  return result;
}
