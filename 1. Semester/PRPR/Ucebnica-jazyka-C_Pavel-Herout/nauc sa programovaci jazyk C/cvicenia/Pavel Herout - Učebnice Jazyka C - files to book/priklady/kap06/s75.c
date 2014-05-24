/*
 * s75.c    v.2.0
 *
 * Cteni ze souboru a zapis do souboru
 * ===================================
 */

#include <stdio.h>

int main()
{
  FILE *fr, *fw;
  int c;

  fr = fopen("ZNAKY.TXT", "r");
  fw = fopen("KOPIE.TXT", "w");

  c = getc(fr);                 /* cteni prvniho znaku */
  putc(c, fw);                  /* zapis prvniho znaku */
  putc(getc(fr), fw);           /* cteni a zapis druheho znaku */

  fclose(fr);
  fclose(fw);
  return 0;
}

