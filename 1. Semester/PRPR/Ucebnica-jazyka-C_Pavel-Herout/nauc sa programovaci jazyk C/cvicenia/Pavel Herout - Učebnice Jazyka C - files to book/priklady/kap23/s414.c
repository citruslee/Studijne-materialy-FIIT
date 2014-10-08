/*
 * s414.c    v.2.0
 *
 * Okrajove hodnoty realnych cisel
 * ===============================
 */

#include <stdio.h>
#include <math.h>

int main(void)
{
  double d = 5.0;
  double nula = 0.0;
  double nan;
  double nekonecno;

  nekonecno = d / nula;
  nan = nula / nula;

/*  if (nan == NAN)
    printf("%f = neni cislo\n", nan);
*/
  if (isnan(nan) != 0)
    printf("%f = neni cislo\n", nan);

/* printf("cislo je v kategorii %d\n", fpclassify(nekonecno));
*/
  return 0;
}

