/*
 * s266.c    v.2.0
 *
 * Prace s jednotlivymi bity slova pomoci bitovych operaci
 * =======================================================
 */

#include <stdio.h>

#define READ     0x8
#define WRITE    0x10
#define DELETE   0x20

/*
 * funkce pro vypis cisla binarne
 */
void binarne(unsigned int i)
{
  int j;

  printf("Cislo %02X hexa je:          binarne\b\b\b\b\b\b\b", i);
  for (j = 0;  j < 8;  j++)
    printf("\b\b%d", ((i >> j) & 1));
  putchar('\n');
}

int main(void)
{
  unsigned int status = 0;

  binarne(status);

  /* nastaveni vsech na 1 */
  status |= READ | WRITE | DELETE;
  binarne(status);

  /* nastaveni vsech na 0 */
  status &= ~(READ | WRITE | DELETE);
  binarne(status);

  /* nastaveni READ a WRITE na 1 */
  status |= READ | WRITE;
  binarne(status);

  /* nastaveni WRITE na 0 */
  status &= ~WRITE;
  binarne(status);

  /* test zda jsou oba priznaky WRITE a DELETE nulove */
  if (! (status & (WRITE | DELETE)))
    printf("Jsou nulove\n");
  return 0;
}

