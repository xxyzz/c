#include <stdio.h>

/* print Fahrenheit-Celsius table
   for fahr = 0, 20, ..., 300; double-precision floating point version */
int main() {
  double fahr, celsius, lower, upper, step;

  lower = 0;   /* lower limit of temperature table */
  upper = 300; /* upper limit */
  step = 20;   /* step size */

  fahr = lower;
  printf("Fahrenheit    Celsius\n");
  while (fahr <= upper) {
    celsius = (5.0 / 9.0) * (fahr-32.0);
    printf("%10.0f %10.1f\n", fahr, celsius);
    fahr = fahr + step;
  }
}
