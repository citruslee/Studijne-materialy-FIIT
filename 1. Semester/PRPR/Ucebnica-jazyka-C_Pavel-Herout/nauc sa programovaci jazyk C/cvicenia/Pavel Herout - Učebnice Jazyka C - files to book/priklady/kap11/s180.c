/*
 * s180.c    v.2.0
 *
 * Pocet pismen v souboru - pristup do pole pomoci pointeru
 * ========================================================
 */

#include <stdio.h>
#include <ctype.h>

#define POCET   ('Z' - 'A' + 1)

int main(void)
{
  FILE *fr;
  int c, *p_i;
  int pole[POCET];

  for (p_i = pole;  p_i < pole + POCET;  p_i++)
    *p_i = 0;                /* nulovani pole */

  if ((fr = fopen("TEST.TXT", "r")) == NULL) {
    printf("Soubor nelze otevrit.\n");
    return 1;
  }

  while ((c = getc(fr)) != EOF) {
    if (isalpha(c))
      /* precteny znak je pismeno */
      (*(pole + toupper(c) - 'A'))++;
  }

  printf("V souboru byl tento pocet jednotlivych pismen\n");
  for (p_i = pole;  p_i < pole + POCET;  p_i++)
    printf("%c - %d\n", p_i - pole + 'A', *p_i);

  if (fclose(fr) == EOF) {
    printf("Soubor nelze zavrit.\n");
    return 1;
  }

  return 0;
}

