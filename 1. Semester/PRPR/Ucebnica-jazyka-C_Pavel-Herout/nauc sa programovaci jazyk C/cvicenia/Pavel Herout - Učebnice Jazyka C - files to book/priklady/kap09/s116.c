/*
 * s116.c    v.2.0
 *
 * Konverze navratove hodnoty funkce
 * =================================
 */

#include <stdio.h>

int konverze(double d);         /* uplny funkcni prototyp */

int main(void)
{
  printf("Konverze %f na int je: %d\n", 4.5, konverze(4.5));
  return 0;
}

int konverze(double d)
{
  return d;
}

