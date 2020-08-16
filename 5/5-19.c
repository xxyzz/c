#include <ctype.h>  // isalnum, isalpha, isblank
#include <stdio.h>  // getchar, sprintf
#include <string.h> // stripy, strcat

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS, POINTER, POINTER_WITH_PARENS };

int getch(void);
void ungetch(int c);
void rmblanks(int *c);
int gettoken(void);

static char token[MAXTOKEN]; /* last token string */
static char out[1000];       /* output string */
static char buf[BUFSIZE];    /* buffer for ungetch */
static int bufp = 0;         /* next free position in buf */

/* undcl: convert word description to declaration
 * g * * int: int **g
 * g * () int: int (*g)()
 * g [] * int: int *g[]
 */
int main() {
  int type;
  char temp[MAXTOKEN];

  while (gettoken() != EOF) {
    strcpy(out, token);
    while ((type = gettoken()) != '\n')
      if (type == PARENS || type == BRACKETS)
        strcat(out, token);
      else if (type == POINTER) {
        sprintf(temp, "*%s", out);
        strcpy(out, temp);
      } else if (type == POINTER_WITH_PARENS) {
        sprintf(temp, "(*%s)", out);
        strcpy(out, temp);
      } else if (type == NAME) {
        sprintf(temp, "%s %s", token, out);
        strcpy(out, temp);
      } else
        printf("invalid input at %s\n", token);
    printf("%s\n", out);
  }
  return 0;
}

/* return next token */
int gettoken(void) {
  int c;
  char *p = token;

  rmblanks(&c);
  if (c == '(') {
    rmblanks(&c);
    if (c == ')') {
      strcpy(token, "()");
      return PARENS;
    } else {
      ungetch(c);
      return (c == '\n') ? PARENS : '(';
    }
  } else if (c == '[') {
    for (*p++ = (char)c; (*p++ = (char)getch()) != ']';) {
      if (!isalnum(*(p - 1))) {
        ungetch(*--p);
        *p++ = ']';
        break;
      }
    }
    *p = '\0';
    return BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = (char)c; isalnum(c = getch());)
      *p++ = (char)c;
    *p = '\0';
    ungetch(c);
    return NAME;
  } else if (c == '*') {
    int next;
    rmblanks(&next);
    ungetch(next);
    if (next == '(' || next == '[')
      return POINTER_WITH_PARENS;
    return POINTER;
  }
  return c;
}

void rmblanks(int *c) {
  while (isblank(*c = getch()))
    ;
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
