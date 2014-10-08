/*
 * s76.c    v.2.0
 *
 * Cteni radky ze souboru
 * ======================
 */

#include <stdio.h>

int main()
{
  int c;
  FILE *fr;

  fr = fopen("DOPIS.TXT", "r");
  while ((c = getc(fr)) != '\n')
    putchar(c);
  putchar(c);                   /* vypis '\n' - odradkovani */
  fclose(fr);
  return 0;
}

