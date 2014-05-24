/*
 * s372.c    v.2.0
 *
 * Pocet parametru predan v pevnem parametru
 * =========================================
 */

#include <stdio.h>
#include <stdarg.h>

/* scita pouze parametry typu int */
int secti(int kolik, ...)
{
  va_list  argumenty;
  int pom = 0;

  va_start(argumenty, kolik);
  while (--kolik != 0)
    pom += va_arg(argumenty, int);
  va_end(argumenty);

  return pom;
}

int main(void)
{
  printf("Soucet je %d\n", secti(1));
  printf("Soucet je %d\n", secti(3, 10, 20));
  printf("Soucet je %d\n", secti(5, 1, 2, 3, 4));
  return 0;
}

