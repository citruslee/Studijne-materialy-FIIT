/*
 * s330.c    v.2.0
 *
 * Mene zname funkce z <math.h>
 * ============================
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
  int i;
  double g, f;

  printf("%f\n", ceil(3.14));          // 4.000000
  printf("%f\n", floor(3.14));         // 3.000000

  f = frexp(3.14, &i);
  printf("%f x 2^%d\n", f, i);         // 0.785000 x 2^2

  f = modf(-3.14, &g);
  printf("%f + %f\n", g, f);           // -3.000000 + -0.140000

  printf("%f\n", fmod(3.14, 2.0));     // 1.140000
  return 0;
}

