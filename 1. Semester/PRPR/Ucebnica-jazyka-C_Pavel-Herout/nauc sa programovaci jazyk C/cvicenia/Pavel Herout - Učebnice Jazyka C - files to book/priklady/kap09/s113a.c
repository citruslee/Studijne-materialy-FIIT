/*
 * s113a.c    v.2.0
 *
 * Rekurzivni funkce
 * =================
 */

#include <stdio.h>

int fakt(int n)
{
  return ((n <= 0)  ?  1  :  n * fakt(n - 1));
}

int main(void)
{
  int i;

  printf("Zadej cele cislo: ");
  scanf("%d", &i);
  printf("Faktorial je %d\n", fakt(i));
  return 0;
}

