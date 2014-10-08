/*
 * s265.c    v.2.0
 *
 * Zjistovani hodnot jednotlivych bitu
 * ===================================
 */

#include <stdio.h>

#define ERROR        -1
#define BITU_V_CHAR  8

int bit(unsigned int x, unsigned int i)
{
  if (i >= sizeof(x) * BITU_V_CHAR)
    return (ERROR);
  else
    return ((x >> i) & 1);
}

int main(void)
{
  unsigned int i = 0x4A;   /* i = 0100 1010 binarne */
  int j;

  printf("Cislo i = %X hexa, tj.          binarne\b\b\b\b\b\b\b", i);
  for (j = 0;  j < BITU_V_CHAR;  j++)
    printf("\b\b%d", bit(i, j));
  putchar('\n');
  return 0;
}

