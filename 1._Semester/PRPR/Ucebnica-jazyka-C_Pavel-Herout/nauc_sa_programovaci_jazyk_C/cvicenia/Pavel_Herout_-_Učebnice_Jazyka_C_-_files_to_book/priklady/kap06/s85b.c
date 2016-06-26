/*
 * s85b.c    v.2.0
 *
 * Vraceni precteneho znaku zpet do souboru
 * ========================================
 */

#include <stdio.h>

int main()
{
  FILE *fr;
  int c, hodnota = 0;

  if ((fr = fopen("CISLA.TXT", "r")) == NULL) {
    printf("Soubor CISLA.TXT se nepodarilo otevrit.\n");
    return 1;
  }

  while ((c = getc(fr)) == '$')
    ;                /* precte vsechny predchazejici znaky $ */
  ungetc(c, fr);     /* vrati prvni cislici cisla do bufferu */

  fscanf(fr, "%d", &hodnota);
  printf("Nactene cislo = %d\n", hodnota);

  if (fclose(fr) == EOF) {
    printf("Soubor CISLA.TXT se nepodarilo uzavrit.\n");
    return 1;
  }
  return 0;
}

