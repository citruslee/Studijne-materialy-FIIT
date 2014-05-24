/*
 * s114.c    v.2.0
 *
 * Funkce nevracejici typ int - deklarace funkce
 * =============================================
 */

#include <stdio.h>

int main(void)
{
  double pikrat();              /* totez:  double pikrat(), r; */
  double r;

  printf("Zadej polomer: ");
  scanf("%lf", &r);
  printf("Obvod kruhu je %f\n", 2 * pikrat(r));
  return 0;
}

double pikrat(double x)
{
  return (x * 3.14);
}

