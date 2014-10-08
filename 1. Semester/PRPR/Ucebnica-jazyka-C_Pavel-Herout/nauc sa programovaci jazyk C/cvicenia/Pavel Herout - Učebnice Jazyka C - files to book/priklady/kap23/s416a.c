/*
 * s416a.c    v.2.0
 *
 * Minimalni velikost pole
 * =======================
 */

#include <stdio.h>

void vypis_pole(int pole[static 3], int n)
{
  int i;

  for (i = 0;  i < n;  i++)
    printf("%d, ", pole[i]);
}

int main(void)
{
  int a[3], b[2];
  vypis_pole(a, 3);
  vypis_pole(b, 2);

  return 0;
}

