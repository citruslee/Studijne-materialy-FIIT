/*
 * s186.c    v.2.0
 *
 * Ukazka chybne inicializace - data jsou lokalni ve stacku
 * ========================================================
 */

#include <stdio.h>

double *init(void)
{
  /* static */ double a[5];
  int i;

  for (i = 0;  i < 5;  i++) {
    printf("Zadej %d. cislo: ", i + 1);
    scanf("%lf", &a[i]);
  }

  return a;
}

int main(void)
{
  double *p_dbl;
  int i;

  p_dbl = init();

  /* k poskozeni stacku dojde volanim jakekoliv funkce - napr. printf() */
  printf("Pole bylo inicializovano takto:\n");

  for (i = 0;  i < 5;  i++)
    printf("%d. prvek = %f\n", i, *(p_dbl + i));
  return 0;
}

