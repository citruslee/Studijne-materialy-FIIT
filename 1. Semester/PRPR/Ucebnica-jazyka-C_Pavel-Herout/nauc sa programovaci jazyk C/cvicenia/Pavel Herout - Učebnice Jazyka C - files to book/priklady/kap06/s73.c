/*
 * s73.c    v.2.0
 *
 * Zapis cisel do souboru
 * ======================
 */

#include <stdio.h>

int main()
{
  FILE *fw;
  int  i;

  fw = fopen("POKUS.TXT", "w");
  for (i = 1;  i <= 10;  i++)
    fprintf(fw, "%d\n", i);
  fclose(fw);
  return 0;
}

