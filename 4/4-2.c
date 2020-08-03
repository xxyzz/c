#include <ctype.h> // isspace, isdigit
#include <stdio.h>
#include <math.h> // pow

double atof(char s[]);

int main(void) {
  printf("atof(\"123.45e-6\"): %g\n", atof("123.45e-6"));
  return 0;
}

/* atof:  convert string s to double */
double atof(char s[]) {
  double val, power;
  int i, sign, exp_sign = 0, exp = 0;

  for (i = 0; isspace(s[i]); i++) /* skip white space */
    ;
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '+')
    i++;
  for (val = 0.0; isdigit(s[i]); i++)
    val = 10.0 * val + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++) {
    val = 10.0 * val + (s[i] - '0');
    power *= 10.0;
  }

  if (tolower(s[i]) == 'e')
    i++;
  if (s[i] == '-') {
    i++;
    exp_sign = -1;
  }
  if (isdigit(s[i]))
    exp = s[i] - '0';

  double result = sign * val / power;
  if (exp) {
    if (exp_sign == -1)
      result /= pow(10, exp);
    else
      result *= pow(10, exp);
  }

  return result;
}
