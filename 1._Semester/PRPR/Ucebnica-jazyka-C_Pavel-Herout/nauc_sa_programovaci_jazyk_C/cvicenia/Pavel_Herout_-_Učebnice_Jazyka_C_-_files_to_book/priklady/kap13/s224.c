/*
 * s224.c    v.2.0
 *
 * Dvourozmerne pole jako skutecny parametr funkce
 * ===============================================
 */

#include <stdio.h>

double maxim(double pole[][4], int radky)
{
  double pom = pole[0][0];
  int    i, j;

  for (i = 0;  i < radky;  i++) {
    for (j = 0;  j < 4;  j++) {
      if (pole[i][j] > pom)
        pom = pole[i][j];
    }
  }
  return pom;
}

int main(void)
{
  int i, j;
  double d[10][4];

  for (i = 0;  i < 10;  i++) {
    for (j = 0;  j < 4;  j++) {
      d[i][j] = i * j;
    }
  }

  printf("Nejvetsi prvek pole je: %f\n", maxim(d, 10));
  return 0;
}

