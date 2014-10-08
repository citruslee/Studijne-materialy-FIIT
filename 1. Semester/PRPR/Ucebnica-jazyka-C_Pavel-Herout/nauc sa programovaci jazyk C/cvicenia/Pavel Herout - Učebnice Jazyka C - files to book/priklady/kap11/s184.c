/*
 * s184.c       v.2.0
 *
 * Pole jako skutecny parametr funkce
 * ==================================
 */

#include <stdio.h>

#define POCET  10

/* funkcni prototyp funkce maxim() je nutny - maxim() vraci
   typ double */
double maxim(double pole[], int pocet);

int main(void)
{
  double f[POCET];
  int i;

  for (i = 0;  i < POCET;  i++) {
    printf("Zadej %d. cislo: ", i + 1);
    scanf("%lf", &f[i]);
  }
  printf("Max. z %d cislic je %f\n", POCET, maxim(f, POCET));
  printf("Max. z casti pole je %f\n", maxim(&f[2], 5));
  return 0;
}

double maxim(double pole[], int pocet)
{
  double *p_max = pole;
  double *p_pom;

  for (p_pom = pole + 1;  p_pom < pole + pocet;  p_pom++) {
    if (*p_pom > *p_max)
      p_max = p_pom;        /* zmena pointeru na max. prvek */
  }
  return *p_max;
}

