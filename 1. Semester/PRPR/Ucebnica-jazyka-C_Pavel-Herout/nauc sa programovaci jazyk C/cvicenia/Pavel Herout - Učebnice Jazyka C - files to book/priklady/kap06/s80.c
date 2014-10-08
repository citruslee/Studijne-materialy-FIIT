/*
 * s80.c    v.2.0
 *
 * Kopirovani souboru s osetrenim otevirani a uzavirani souboru
 * ============================================================
 */

#include <stdio.h>

int main()
{
  FILE *fr, *fw;
  int c;

  if ((fr = fopen("ORIG.TXT", "r")) == NULL) {
    printf("Soubor ORIG.TXT se nepodarilo otevrit\n");
    return 1;            /* ukonceni programu, kde 1 znamena 'chyba' */
  }

  if ((fw = fopen("KOPIE.TXT", "w")) == NULL) {
    printf("Soubor KOPIE.TXT se nepodarilo otevrit\n");
    return 1;            /* ukonceni programu */
  }

  while ((c = getc(fr)) != EOF)
    putc(c, fw);

  if (fclose(fr) == EOF) {
    printf("Soubor ORIG.TXT se nepodarilo uzavrit\n");
    return 1;            /* nevhodne */
  }

  if (fclose(fw) == EOF) {
    printf("Soubor KOPIE.TXT se nepodarilo uzavrit\n");
    return 1;
  }
  return 0;
}

