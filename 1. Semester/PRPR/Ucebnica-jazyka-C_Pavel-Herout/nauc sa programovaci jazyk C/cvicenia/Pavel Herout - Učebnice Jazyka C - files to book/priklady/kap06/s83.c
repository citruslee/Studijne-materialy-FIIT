/*
 * s83.c    v.2.0
 *
 * Vyuziti stdout - prepinani vystupu na terminal nebo do souboru
 * ==============================================================
 */

#include <stdio.h>

int main()
{
  FILE *fw;
  int c;

  printf("Stisknete O pro vypis na Obrazovku\n");
  printf("nebo jiny znak pro zapis do souboru VYSTUP.TXT: ");

  c = getchar();
  /* vyprazdneni bufferu - preskoci zbytek radky */
  while (getchar() != '\n')
    ;

  if (c == 'o'  ||  c == 'O')
    fw = stdout;
  else {
    if ((fw = fopen("VYSTUP.TXT", "r")) != NULL) {
      printf("Soubor VYSTUP.TXT existuje, prepsat? [A/N]: ");
      c = getchar();
      while (getchar() != '\n')
        ;
      if (fclose(fw) == EOF) {
        printf("Chyba pri uzavirani souboru\n");
        return 1;
      }

      if ( !(c == 'a'  ||  c == 'A') )
        return 0;    /* konec programu - nechce prepsat soubor */
    }

    if ((fw = fopen("VYSTUP.TXT", "w")) == NULL) {
      printf("Soubor VYSTUP.TXT se nepodarilo otevrit\n");
      return 1;
    }
  }

  printf("Piste text a ukoncete jej znakem *\n");
  while ((c = getchar()) != '*')
    putc(c, fw);

  if (fw != stdout) {
    if (fclose(fw) == EOF) {
      printf("Soubor VYSTUP.TXT se nepodarilo uzavrit\n");
      return 1;
    }
  }
  return 0;
}

