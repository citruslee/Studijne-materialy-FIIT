/*
 * s119.c    v.2.0
 *
 * Sdileni globalni promenne mezi funkcemi
 * =======================================
 */

#include <stdio.h>

#define CHYBA(zprava)   { printf("%s\n", zprava); return 1; }

FILE *fr;

/*
 * otevira soubor DOPIS.TXT
 * vraci nenulovou hodnotu pri uspesnem otevreni, jinak vraci 0
 */
int otevri_soubor(void)
{
  return ((fr = fopen("DOPIS.TXT", "r")) != NULL);
}

/*
 * zavira soubor DOPIS.TXT
 * vraci nenulovou hodnotu pri uspesnem zavreni, jinak vraci 0
 */
int zavri_soubor(void)
{
  return (fclose(fr) != EOF);
}

/*
 * cte radku ze souboru
 * vraci delku prectene radky nebo EOF pri konci souboru
 */
int cti_radku(void)
{
  int delka = 0,
      c;

  while ((c = getc(fr)) != EOF) {
    if (c == '\n')
      return (delka + 1);
    else
      delka++;
  }
  return (EOF);
}

int main(void)
{
  int nejdelsi = 0,
      aktualni;

  if (otevri_soubor() == 0)
    CHYBA("Nelze otevrit soubor DOPIS.TXT")

  while ((aktualni = cti_radku()) != EOF) {
    if (aktualni > nejdelsi)
      nejdelsi = aktualni;
  }

  printf("Delka nejdelsi radky je %d\n", nejdelsi);

  if (zavri_soubor() == 0)
    CHYBA("Nelze zavrit soubor DOPIS.TXT")

  return 0;
}
