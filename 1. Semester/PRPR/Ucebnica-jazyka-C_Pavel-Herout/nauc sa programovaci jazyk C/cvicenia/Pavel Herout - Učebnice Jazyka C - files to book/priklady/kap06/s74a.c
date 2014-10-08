/*
 * s74a.c    v.2.0
 *
 * Cteni cisel ze souboru
 * ======================
 */

#include <stdio.h>

int main()
{
  FILE *fr;
  double x, y, z;

  fr = fopen("DATA.TXT", "r");
  fscanf(fr, "%lf %lf %lf", &x, &y, &z);
  printf("%f\n", x + y + z);
  fclose(fr);
  return 0;
}

