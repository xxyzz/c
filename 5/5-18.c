#include <ctype.h>  // isalnum
#include <stdio.h>  // getchar
#include <string.h> // stripy, strcat

#define MAXTOKEN 100
#define BUFSIZE 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);
int getch(void);
void ungetch(int c);
void rmblanks(int *c);
int gettoken(void);

static int tokentype;           /* type of last token */
static char token[MAXTOKEN];    /* last token string */
static char name[MAXTOKEN];     /* identifier name */
static char datatype[MAXTOKEN]; /* data type = char, int, etc. */
static char out[1000];          /* output string */
static char buf[BUFSIZE];       /* buffer for ungetch */
static int bufp = 0;            /* next free position in buf */

/* convert declaration to words
 *
 * char (*(*x())[)(), char ( * ( * x ( ) ) [ ) ( )
 * x:  function returning pointer to array[] of
 * pointer to function returning char
 *
 * int x(, int x (  ), int x (
 * x:  function returning int
 */
int main() {
  while (gettoken() != EOF) { /* 1st token on line */
    strcpy(datatype, token);  /* is the datatype */
    out[0] = '\0';
    dcl(); /* parse rest of line */
    if (tokentype != '\n') {
      printf("syntax error\n");
      while (getch() != '\n') /* discard rest of line */
        ;
    }
    printf("%s: %s %s\n", name, out, datatype);
  }
  return 0;
}

/* dcl: parse a declarator */
void dcl(void) {
  int ns;

  for (ns = 0; gettoken() == '*';) /* count *′s */
    ns++;
  dirdcl();
  while (ns-- > 0)
    strcat(out, " pointer to");
}

/* dirdcl: parse a direct declarator */
void dirdcl(void) {
  int type;

  if (tokentype == '(') { /* ( dcl ) */
    dcl();
    if (tokentype != ')')
      printf("error: missing )\n");
  } else if (tokentype == NAME) /* variable name */
    strcpy(name, token);
  else
    printf("error: expected name or (dcl)\n");
  while ((type = gettoken()) == PARENS || type == BRACKETS)
    if (type == PARENS)
      strcat(out, " function returning");
    else {
      strcat(out, " array");
      strcat(out, token);
      strcat(out, " of");
    }
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
      return tokentype = PARENS;
    } else {
      ungetch(c);
      return tokentype = (c == '\n') ? PARENS : '(';
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
    return tokentype = BRACKETS;
  } else if (isalpha(c)) {
    for (*p++ = (char)c; isalnum(c = getch());)
      *p++ = (char)c;
    *p = '\0';
    ungetch(c);
    return tokentype = NAME;
  } else
    return tokentype = c;
}

void rmblanks(int *c) {
  while ((*c = getch()) == ' ' || *c == '\t')
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
