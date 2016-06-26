/*
 * s417.c    v.2.0
 *
 * Identifikator funkce
 * ====================
 */

#include <stdio.h>

#define LADENI


#ifdef LADENI
  #define IDENTIFIKACE printf("-> %s\n", __func__)
#else
  #define IDENTIFIKACE
#endif

void moje_funkce(void)
{
  IDENTIFIKACE;
  printf("telo funkce\n");
}

int main(void)
{
  moje_funkce();

  return 0;
}

