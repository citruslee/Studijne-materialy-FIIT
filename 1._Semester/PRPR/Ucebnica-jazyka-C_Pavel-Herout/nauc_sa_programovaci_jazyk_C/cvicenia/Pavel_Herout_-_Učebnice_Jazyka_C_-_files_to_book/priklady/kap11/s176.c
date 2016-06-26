/*
 * s176.c    v.2.0
 *
 * Pocet pismen v souboru
 * ======================
 */

#include <stdio.h>
#include <ctype.h>

#define POCET   ('Z' - 'A' + 1)

int main(void)
{
  FILE *fr;
  int c, i;
  int pole[POCET];

  for (i = 0;  i < POCET;  i++)
    pole[i] = 0;                /* nulovani pole */

  if ((fr = fopen("TEST.TXT", "r")) == NULL) {
    printf("Soubor nelze otevrit.\n");
    return 1;
  }

  while ((c = getc(fr)) != EOF) {
    if (isalpha(c))
      /* precteny znak je pismeno */
      pole[toupper(c) - 'A']++;
  }

  printf("V souboru byl tento pocet jednotlivych pismen\n");
  for (i = 0;  i < POCET;  i++)
    printf("%c - %d\n", i + 'A', pole[i]);

  if (fclose(fr) == EOF) {
    printf("Soubor nelze zavrit.\n");
    return 1;
  }

  return 0;
}

