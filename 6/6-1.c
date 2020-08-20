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

/* count C keywords */
int main() {
  char word[MAXWORD];

  while (getword(word, MAXWORD) != EOF)
    if (isalpha(word[0]))
      printf("%s\n", word);
  return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim) {
  int c, getch(void);
  void ungetch(int);
  char *w = word;
  int previous = '\0', next = '\0';

  while (isspace(c = getch()))
    ;
  if (c != EOF && c != '#')
    *w++ = (char)c;

  if (isalpha(c) || c == '_' || c == '#') {
    for (; --lim > 0; w++)
      if (!isalnum(*w = (char)getch()) && *w != '_') {
        ungetch(*w);
        break;
      }
  } else if (c == '/') {
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
  } else if (c == '\'') { // char: 'x', '\t'
    int after_quote = 0, pre = '\0', prepre = '\0';
    while ((c = getch())) {
      ++after_quote;
      if (c == '\'' && pre != '\\' && after_quote == 2)
        break;
      else if (c == '\'' && prepre == '\\' && after_quote == 3)
        break;
      prepre = pre;
      pre = c;
    }
  } else {
    *w = '\0';
    return c;
  }

  *w = '\0';
  return word[0];
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
