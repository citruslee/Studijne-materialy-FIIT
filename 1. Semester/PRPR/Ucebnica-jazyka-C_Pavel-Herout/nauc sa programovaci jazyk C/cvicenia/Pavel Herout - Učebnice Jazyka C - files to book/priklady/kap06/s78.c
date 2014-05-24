/*
 * s78.c    v.2.0
 *
 * Kopirovani souboru pomoci funkce feof()
 * =======================================
 */

#include <stdio.h>

int main()
{
  FILE *fr, *fw;
  int c;
  fr = fopen("ORIG.TXT", "r");
  fw = fopen("KOPIE.TXT", "w");

  while (c = getc(fr), feof(fr) == 0) {
    putc(c, fw);
  }

  fclose(fr);
  fclose(fw);
  return 0;
}

