/*
 * s126.c    v.2.0
 *
 * Definice uvnitr bloku
 * =====================
 */

#include <stdio.h>

int main(void)
{
  int i;

  scanf("%d", &i);
  if (i > 0) {
    static int j;                /* j definovano uvnitr bloku */
    scanf("%d", &j);
    printf("Soucet je %d\n", i + j);
  }
  else {
    double f;                   /* f definovano uvnitr bloku */
    scanf("%lf", &f);
    printf("Soucin je %f\n", i * f);
  }
  return 0;
}

