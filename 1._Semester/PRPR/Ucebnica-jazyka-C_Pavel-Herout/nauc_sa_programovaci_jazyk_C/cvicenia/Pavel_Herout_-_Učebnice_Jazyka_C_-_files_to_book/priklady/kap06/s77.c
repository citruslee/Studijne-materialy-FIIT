/*
 * s77.c    v.2.0
 *
 * Kopirovani souboru pomoci EOF
 * =============================
 */

#include <stdio.h>

int main()
{
  FILE *fr, *fw;
  int c;
  fr = fopen("ORIG.TXT", "r");
  fw = fopen("KOPIE.TXT", "w");

  while ((c = getc(fr)) != EOF)
    putc(c, fw);

  fclose(fr);
  fclose(fw);
  return 0;
}

