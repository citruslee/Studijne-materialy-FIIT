/*
 * s81.c    v.2.0
 *
 * Vypis souboru na obrazovku s konverzi malych pismen
 * ===================================================
 */

#include <stdio.h>

int main()
{
  FILE *fr;
  int c,
      nejdelsi = 0,
      pocet = 0;

  if ((fr = fopen("DOPIS.TXT", "r")) == NULL) {
    printf("Soubor DOPIS.TXT se nepodarilo otevrit\n");
    return 1;     /* konec kvuli chybe */
  }

  while ((c = getc(fr)) != EOF) {
    putchar(c >= 'a'  &&  c <= 'z'  ?  c + 'A' - 'a'  :  c);
    if (c == '\n') {
      if (nejdelsi < pocet)
        nejdelsi = pocet;
      pocet = 0;
    }
    else
      pocet++;
  }
  printf("Nejdelsi radka obsahovala %d znaku.\n", nejdelsi);

  if (fclose(fr) == EOF) {
    printf("Soubor DOPIS.TXT se nepodarilo uzavrit\n");
    return 1;     /* konec kvuli chybe */
  }
  return 0;       /* 0 znamena konec bez chyby */
}

