#include <ctype.h>  // isalnum, isblank
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
int iskeyword(const char *s);

static int tokentype;           /* type of last token */
static char token[MAXTOKEN];    /* last token string */
static char name[MAXTOKEN];     /* identifier name */
static char datatype[MAXTOKEN]; /* data type = char, int, etc. */
static char out[1000];          /* output string */
static char buf[BUFSIZE];       /* buffer for ungetch */
static int bufp = 0;            /* next free position in buf */
static char *keywords[] = {"const",  "volatile", "static",   "void",  "char",
                           "short",  "int",      "long",     "float", "double",
                           "signed", "unsigned", "register", "extern"};

/* convert declaration to words
 *
 * unsigned char (*f)(int, char *, const char *)
 * f:  pointer to  function with parameter of int , pointer to char ,
 * pointer to const char  returning unsigned char
 *
 * void qsort(void *[], int, int, int (*)(void *, void *))
 * qsort:  function with parameter of array[] of pointer to void ,int ,int ,
 * pointer to  function with parameter of  pointer to void , pointer to void
 * returning int  returning  void
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
    strcat(out, " pointer to ");
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
  else if (tokentype == ',' || tokentype == ')')
    return;
  else if (tokentype == BRACKETS) {
    strcat(out, "array");
    strcat(out, token);
    strcat(out, " of");
  }

  while ((type = gettoken()) == PARENS || type == BRACKETS || type == '(')
    if (type == PARENS)
      strcat(out, "function returning");
    else if (type == BRACKETS) {
      strcat(out, "array");
      strcat(out, token);
      strcat(out, " of");
    } else if (type == '(') { /* (dcl, dcl)  */
      tokentype = '\0';
      char paratype[MAXTOKEN];
      strcat(out, " function with parameter of ");
      do {
        gettoken();
        strcpy(paratype, token);
        dcl();
        strcat(out, paratype);
        if (tokentype == ',')
          strcat(out, ",");
      } while (tokentype == ',');
      strcat(out, " returning ");
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
    char s[MAXTOKEN];
    token[0] = '\0';
    while (1) {
      int i = 0;
      for (s[i++] = (char)c; isalnum(c = getch()) && i < MAXTOKEN - 2;)
        s[i++] = (char)c;
      s[i] = '\0';
      if (!iskeyword(s)) {
        ungetch(c);
        if (!token[0])
          strcat(token, s); // function or variable name
        else
          while (i)
            ungetch(s[--i]);
        break;
      }
      s[i++] = ' ';
      s[i] = '\0';
      strcat(token, s); // append keyword
      ungetch(c);
      rmblanks(&c);
      if (!isalpha(c)) {
        ungetch(c);
        break;
      }
    }
    return tokentype = NAME;
  } else
    return tokentype = c;
}

void rmblanks(int *c) {
  while (isblank(*c = getch()))
    ;
}

int iskeyword(const char *s) {
  for (size_t i = 0; i < sizeof(keywords) / sizeof(char *); i++) {
    if (strcmp(keywords[i], s) == 0)
      return 1;
  }
  return 0;
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
