/*
 * signal-nula.c    v.2.0
 *
 * Jak zajistit svoji vlastni reakci, kdyz se nekde v programu deli nulou
 * ======================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void obsluha_signalu(int nevyuzity_parametr)
{
  printf("Deleni nulou\n");
  exit(1);
}

int main(void)
{
  int i = 5;
  int j = 0;
  signal(SIGFPE, obsluha_signalu);
  i = i / j;

  return 0;
}

