/*
 * asr.c    v.2.0
 *
 * Chybne pouziti assert()
 * =======================
 */

#include <stdio.h>
#include <assert.h>

int main(void)
{
  FILE *fr;
  int c;

  if ((fr = fopen("POKUS.TXT", "r")) == NULL)
    printf("Soubor POKUS.TXT se nepodarilo otevrit\n");
  else {
    while ((c = getc(fr)) != EOF)
      putchar(c);

    if (fclose(fr) == EOF)
      printf("1. Soubor POKUS.TXT se nepodarilo uzavrit.\n");
  }

  assert((fr = fopen("POKUS.TXT", "r")) != NULL);
  while ((c = getc(fr)) != EOF)
    putchar(c);

  if (fclose(fr) == EOF)
    printf("2. Soubor POKUS.TXT se nepodarilo uzavrit.\n");

  return 0;
}

