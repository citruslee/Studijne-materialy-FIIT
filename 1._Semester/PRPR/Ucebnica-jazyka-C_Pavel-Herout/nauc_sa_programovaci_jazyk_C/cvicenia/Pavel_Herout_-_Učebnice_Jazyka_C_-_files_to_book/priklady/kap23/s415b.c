/*
 * s408.c    v.2.0
 *
 * Promenna delka lokalniho pole
 * =============================
 */

#include <stdio.h>

void vypis_pole(int n)
{
  int pole[n * 2];
  int i, d;
  d = sizeof(pole) / sizeof(int);

  for (i = 0;  i < d;  i++)
    printf("%d, ", pole[i]);
}

int main(void)
{
  vypis_pole(2);

  return 0;
}

