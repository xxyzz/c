#include <ctype.h>  // isalpha, isspace, isalnum
#include <stdio.h>  // EOF
#include <string.h> // strcmp

#define MAXWORD 100
#define BUFSIZE 100

static char buf[BUFSIZE]; /* buffer for ungetch */
static int bufp = 0;      /* next free position in buf */

int getword(char *, int);
int getch(void);
void ungetch(int c);
int filter(void);

/* count C keywords */
int main() {
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF)
    printf("%s\n", word);
  return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;

  c = filter();
  if (c != EOF)
    *w++ = (char)c;

  if (!isalpha(c) && c != '_') {
    *w = '\0';
    return c; // non-alphabetic character or EOF
  }
  for (; --lim > 0; w++)
    if (!isalnum(*w = (char)getch()) && *w != '_') {
      ungetch(*w);
      break;
    }
  *w = '\0';
  return word[0];
}

/* filter unwanted characters */
int filter() {
  int c, previous = '\0', next = '\0';
  while (isspace(c = getch()))
    ;
  if (c == '/') {
    next = getch();
    if (next == '/') { // single line comment
      while ((c = getch()))
        if (c == '\n')
          break;
    } else if (next == '*') { // multi-line comment
      while ((c = getch())) {
        if (previous == '*' && c == '/')
          break;
        previous = c;
      }
    }
  } else if (c == '"') { // string
    while ((c = getch())) {
      if (previous != '\\' && c == '"')
        break;
      previous = c;
    }
  } else if (c == '#') { // preprocessor control lines
    while ((c = getch()))
      if (c == '\n')
        break;
  } else
    return c;
  return filter(); // check again
}

/* get a (possibly pushed back) character */
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }

/* push character back on input */
void ungetch(int c) {
  if (bufp >= BUFSIZE)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = (char)c;
}
