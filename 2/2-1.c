#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdio.h>
#include <string.h> // memcpy
// https://en.wikipedia.org/wiki/C_data_types

int main() {
  // ~0: all 1s
  // >> 1: remove sign bit

  // char 8 bits
  // signed: -128 - 127
  // 1000 0000: -128
  // 0111 1111: 127
  // 1111 1111: -1
  // https://en.wikipedia.org/wiki/Two's_complement
  printf("signed char range from header: %d - %d\n", SCHAR_MIN, SCHAR_MAX);
  printf("signed char range from computation: %d - %d\n",
         ~(signed char)((unsigned char)~0 >> 1),
         (signed char)((unsigned char)~0 >> 1));
  // unsigned: 0 - 255
  printf("unsigned char range from header: 0 - %d\n", UCHAR_MAX);
  printf("unsigned char range from computation: 0 - %d\n\n", (unsigned char)~0);

  // short 16 bits
  // signed: -32768 - 32767
  // unsigned: 0 - 65535
  printf("signed short range from header: %d - %d\n", SHRT_MIN, SHRT_MAX);
  printf("signed short range from computation: %d - %d\n",
         ~(signed short)((unsigned short)~0 >> 1),
         (signed short)((unsigned short)~0 >> 1));
  printf("unsigned short range from header: 0 - %d\n", USHRT_MAX);
  printf("unsigned short range from computation: 0 - %d\n\n",
         (unsigned short)~0);

  // int 32 bits
  // signed: -2147483648 - 2147483647
  // unsigned: 0 - 4294967295
  printf("signed int range from header: %d - %d\n", INT_MIN, INT_MAX);
  printf("signed int range from computation: %d - %d\n",
         ~(signed int)((unsigned int)~0 >> 1),
         (signed int)((unsigned int)~0 >> 1));
  printf("unsigned int range from header: 0 - %u\n", UINT_MAX);
  printf("unsigned int range from computation: 0 - %u\n\n", (unsigned int)~0);

  // long 64 bits
  // signed: -9223372036854775808 - 9223372036854775807
  // unsigned: 0 - 18446744073709551615
  printf("signed long range from header: %ld - %ld\n", LONG_MIN, LONG_MAX);
  printf("signed long range from computation: %ld - %ld\n",
         ~(signed long)((unsigned long)~0 >> 1),
         (signed long)((unsigned long)~0 >> 1));
  printf("unsigned long range from header: 0 - %lu\n", ULONG_MAX);
  printf("unsigned long range from computation: 0 - %lu\n\n",
         (unsigned long)~0);

  // long long
  // same as long
  printf("signed long long range from header: %lld - %lld\n", LLONG_MIN,
         LLONG_MAX);
  printf("signed long long range from computation: %lld - %lld\n",
         ~(signed long long)((unsigned long long)~0 >> 1),
         (signed long long)((unsigned long long)~0 >> 1));
  printf("unsigned long long range from header: 0 - %llu\n", ULLONG_MAX);
  printf("unsigned long long range from computation: 0 - %llu\n\n",
         (unsigned long long)~0);

  // Radix of exponent representation, b.
  // FLT_RADIX: 2
  printf("FLT_RADIX: %d\n", FLT_RADIX);
  // Number of base-FLT_RADIX digits in the significand, p.
  // FLT_MANT_DIG: 24, DBL_MANT_DIG: 53, LDBL_MANT_DIG: 64
  printf("FLT_MANT_DIG: %d, DBL_MANT_DIG: %d, LDBL_MANT_DIG: %d\n",
         FLT_MANT_DIG, DBL_MANT_DIG, LDBL_MANT_DIG);
  // Minimum int x such that FLT_RADIX**(x-1) is a normalized float, emin.
  // FLT_MIN_EXP: -125, DBL_MIN_EXP: -1021, LDBL_MIN_EXP: -16381
  printf("FLT_MIN_EXP: %d, DBL_MIN_EXP: %d, LDBL_MIN_EXP: %d\n", FLT_MIN_EXP,
         DBL_MIN_EXP, LDBL_MIN_EXP);
  // Maximum int x such that FLT_RADIX**(x-1) is a representable float, emax.
  // FLT_MAX_EXP: 128, DBL_MAX_EXP: 1024, LDBL_MAX_EXP: 16384
  printf("FLT_MAX_EXP: %d, DBL_MAX_EXP: %d, LDBL_MAX_EXP: %d\n", FLT_MAX_EXP,
         DBL_MAX_EXP, LDBL_MAX_EXP);
  /*
   * FLT_EPSILON:  1.19209e-07 = 2^-23
   * DBL_EPSILON:  2.22045e-16 = 2^-52
   * LDBL_EPSILON: 1.0842e-19  = 2^-63
   */
  printf("FLT_EPSILON: %g, DBL_EPSILON: %g, LDBL_EPSILON: %Lg \n\n",
         FLT_EPSILON, DBL_EPSILON, LDBL_EPSILON);

  /*
   * float 32 bits
   * Maximum representable finite floating-point number,
   * (1 - b**-p) * b**emax
   * = (1 - 2^-24) * 2^128
   * = 340282346638528859811704183484516925440.000000 (%f)
   * = 3.40282e+38
   */
  printf("largest normal float from header: %g\n", FLT_MAX);
  /*
   * 0      1111 1110         1111 1111 1111 1111 1111 111
   * 31     30                22                         0
   * sign   biased exponent   precision / trailing significand field
   * 2^(2^8 - 2 - 127) * (1 + 2^-1 + 2^-2 + ... + 2^-23)
   * 2^(254-127) * (1 + 2^-1 + 2^-2 + ... + 2^-23)
   * = 2^127 * 2 * (1 - 2^-24)
   */
  unsigned temp1 = 0x7F7FFFFFU;
  float max_float = 0;
  memcpy(&max_float, &temp1, sizeof(temp1));
  printf("largest normal float: %g %g\n", max_float,
         powf(FLT_RADIX, FLT_MAX_EXP - 1) *
             (2 - powf(FLT_RADIX, 1 - FLT_MANT_DIG)));
  /*
   * 0    0000 0001 0000 0000 0000 0000 0000 000
   * 31   30        22                         0
   * 2^(1 - 127) = 2^-126
   * b**(emin - 1) = 2 ^ (-125 - 1)
   */
  printf("smallest positive normal float from header: %g\n",
         FLT_MIN); // 1.17549e-38
  temp1 = 0x800000U;
  float min_float = 0;
  memcpy(&min_float, &temp1, sizeof(temp1));
  printf("smallest positive normal float: %g %g\n", min_float,
         powf(FLT_RADIX, FLT_MIN_EXP - 1));
  /*
   * 0 00000000 00000000000000000000000: +0
   * 1 00000000 00000000000000000000000: -0
   */
  temp1 = 0x0U;
  float zero = 0;
  memcpy(&zero, &temp1, sizeof(temp1));
  printf("positive zero: %g\n", zero);
  temp1 = 0x80000000U;
  memcpy(&zero, &temp1, sizeof(temp1));
  printf("negative zero: %g\n", zero);
  /*
   * 0 11111111 00000000000000000000000: infinity
   * 1 11111111 00000000000000000000000: −infinity
   */
  temp1 = 0x7F800000U;
  float inf = 0;
  memcpy(&inf, &temp1, sizeof(temp1));
  printf("positive infinity: %g\n", inf);
  temp1 = 0xFF800000U;
  memcpy(&inf, &temp1, sizeof(temp1));
  printf("negative infinity: %g\n", inf);
  /*
   * 0/1 11111111 10000000000000000000001: qNaN
   * 0/1 11111111 00000000000000000000001: sNaN
   */
  temp1 = 0x7FC00001U;
  float nan = 0;
  memcpy(&nan, &temp1, sizeof(temp1));
  printf("quiet NaN: %g\n", nan);
  temp1 = 0x7F800001U;
  memcpy(&nan, &temp1, sizeof(temp1));
  printf("signaling NaN: %g\n\n", nan);

  /*
   * double 64 bits
   * (1 - 2^-53) * 2^1024
   * 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000
   * (%lf) = 1.79769e+308
   */
  printf("largest normal double from header: %g\n", DBL_MAX);
  /*
   * 0  11111111110 1111111111111111111111111111111111111111111111111111
   * 63             51                                                 0
   * 2^(2^11 - 2 - 1023) * (1 + 2^-1 + ... + 2^-52)
   * = 2^(2046 - 1023) * ...
   * = 2^1023 * 2 * (1 - 2^-53)
   */
  unsigned long temp2 = 0x7FEFFFFFFFFFFFFFUL;
  double max_double = 0;
  memcpy(&max_double, &temp2, sizeof(temp2));
  printf("largest normal double: %g\n\n", max_double);

  /*
   * long double 80 bits
   * (1 - 2^-64) * 2^16384 = 1.18973e+4932
   */
  printf("largest long double from header: %Lg\n", LDBL_MAX);
  printf("largest long double: %Lg\n",
         (2 - powl(FLT_RADIX, 1 - LDBL_MANT_DIG)) *
             powl(FLT_RADIX, LDBL_MAX_EXP - 1));
  printf("smallest positive long double from header: %Lg\n", LDBL_MIN);
  printf("smallest positive long double: %Lg\n",
         powl(FLT_RADIX, LDBL_MIN_EXP - 1));

  /*
   * use `gcc/clang -H 2-1.c` to find the header file's path
   * or https://gcc.gnu.org/git/?p=gcc.git;a=blob;f=gcc/ginclude/float.h;hb=HEAD
   * https://github.com/llvm/llvm-project/blob/main/clang/lib/Headers/float.h
   * DBL_MIN: it's near 0
   * Minimum normalized positive floating-point number, b**(emin - 1).
   *
   * Floating-point gap:
   * https://github.com/xxyzz/SICP/blob/master/1_Building_Abstractions_with_Procedures/1.1_The_Elements_of_Programming/Exercise_1_7.rkt
   *
   * RTFM:
   * https://en.wikipedia.org/wiki/Single-precision_floating-point_format
   * https://en.wikipedia.org/wiki/Double-precision_floating-point_format
   * https://en.wikipedia.org/wiki/Extended_precision
   * IEEE 754 doi:10.1109/ieeestd.2019.8766229
   * What Every Computer Scientist Should Know About Floating-Point Arithmetic
   */

  return 0;
}
