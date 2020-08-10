#include <ctype.h>  // isspace, isdigit, tolower
#include <math.h>   // pow
#include <stdio.h>  // getline
#include <string.h> // strlen
#include <stdlib.h> // free

#define NUMBER '0' /* signal that a number was found */

int my_getline(char *s, int lim);
double my_atof(const char *s);
int my_atoi(const char *s);
void my_itoa(int n, char *s);
void reverse(char *s);
int strindex(const char *s, const char *t);
int getop(char *s);

static char *line = NULL;
static int li = 0;
static size_t len = 0;

int main() {
  char s[10];
  printf("my_getline(s, 10): %d, %s\n", my_getline(s, 10), s);
  printf("my_atof(\"2.718e-10\"): %g\n", my_atof("2.718e-10"));
  printf("my_atoi(\"42\"): %d\n", my_atoi("42"));
  reverse(s);
  printf("reverse(s): %s\n", s);
  my_itoa(42, s);
  printf("my_itoa(42, s): %s\n", s);
  printf("strindex(\"I'm gonna jam my thumb in its butthole now. This should "
         "REALLY piss it off!\", \"I'm gonna jam my thumb in its butthole "
         "now\"): %d\n",
         strindex("I'm gonna jam my thumb in its butthole now. This should "
                  "REALLY piss it off!",
                  "I'm gonna jam my thumb in its butthole now."));
  printf("strindex(\"Please. Mr. Marsh was only standing up for me and Piglet, "
         "because we were political prisoners.\", \"because we were political "
         "prisoners.\"): %d\n",
         strindex("Please. Mr. Marsh was only standing up for me and Piglet, "
                  "because we were political prisoners.",
                  "because we were political prisoners."));
  printf("getop: %d, %s\n", getop(s), s);
  free(line);
  return 0;
}

/* my_getline: read a line into s, return length */
int my_getline(char *s, int lim) {
  int c, i;

  for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
    if (i < lim - 1)
      *s++ = (char)c;

  *s++ = '\0';
  return i;
}

/* my_atof: convert string s to double */
double my_atof(const char *s) {
  double val, power;
  int sign, exp_sign = 1, exp = 0;

  while (isspace(*s)) /* skip white space */
    s++;
  sign = (*s == '-') ? -1 : 1;
  if (*s == '+' || *s == '+')
    s++;
  for (val = 0.0; isdigit(*s); s++)
    val = 10.0 * val + (*s - '0');
  if (*s == '.')
    s++;
  for (power = 1.0; isdigit(*s); s++) {
    val = 10.0 * val + (*s - '0');
    power *= 10.0;
  }

  if (tolower(*s) == 'e')
    s++;
  if (*s == '-' || *s == '+') {
    if (*s == '-')
      exp_sign = -1;
    s++;
  }
  while (isdigit(*s))
    exp = exp * 10 + (*s++ - '0');

  double result = sign * val / power;
  if (exp) {
    if (exp_sign == -1)
      result /= pow(10, exp);
    else
      result *= pow(10, exp);
  }

  return result;
}

/* my_atoi: convert string s to integer using my_atof */
int my_atoi(const char *s) {
  double num = my_atof(s);
  return (int)num;
}

/* my_itoa: convert n to characters in s */
void my_itoa(int n, char *s) {
  int sign = n;
  char *cp_s = s;

  do { /* generate digits in reverse order */
    int curr = n % 10;
    if (sign < 0)
      curr = -curr;
    *s++ = (char)curr + '0'; /* get next digit */
  } while (n /= 10);         /* delete it */
  if (sign < 0)
    *s++ = '-';
  *s = '\0';
  reverse(cp_s);
}

void reverse(char *s) {
  for (char *t = s + strlen(s) - 1; s < t; s++, t--) {
    char temp = *s;
    *s = *t;
    *t = temp;
  }
}

/* strindex: return the rightmost index of t in s, −1 if none */
int strindex(const char *s, const char *t) {
  int i, index = -1;

  for (i = 0; *s++ != '\0'; i++) {
    while (*t != '\0' && *s++ == *t++)
      ;
    if (*t == '\0')
      index = i;
  }
  return index;
}

/* getop: get next operator or numeric operand */
int getop(char *s) {
  int i = 0, c;

  if (line == NULL || *(line + i) == '\0') {
    if (getline(&line, &len, stdin) == -1)
      return EOF;
    else
      li = 0;
  }

  while ((*s = c = *(line + i)) == ' ' || c == '\t')
    ;
  *(s + 1) = '\0';
  if (!isdigit(c) && c != '.' && c != '-')
    return c; /* not a number */
  if (c == '-') {
    if (isdigit(c = *(line + li++)) || c == '.')
      *s++ = (char)c; // negative number
    else {
      if (c != EOF)
        li--;
      return '-'; // minus sign
    }
  }
  if (isdigit(c)) /* collect integer part */
    while (isdigit(*s++ = c = *(line + i++)))
      ;
  if (c == '.') /* collect fraction part */
    while (isdigit(*s++ = c = *(line + i++)))
      ;
  *s = '\0';
  if (c != EOF)
    li--;
  return NUMBER;
}
