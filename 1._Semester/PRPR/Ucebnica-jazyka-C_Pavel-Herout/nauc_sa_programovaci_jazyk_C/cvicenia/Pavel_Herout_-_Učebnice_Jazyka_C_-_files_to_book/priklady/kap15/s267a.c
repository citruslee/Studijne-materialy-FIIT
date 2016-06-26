/*
 * s267a.c    v.2.0
 *
 * Bitove pole - pouziti pro ulozeni zhusteneho cisla
 * ==================================================
 */

#include <stdio.h>

typedef struct {
  unsigned den    : 5;   /* bity 0 -  4 */
  unsigned mesic  : 4;   /* bity 5 -  8 */
  unsigned rok    : 7;   /* bity 9 - 15 */
} DATUM;

DATUM dnes, zitra;

int main(void)
{
  printf("sizeof(DATUM) = %d\n", sizeof(DATUM));

  dnes.den = 25;
  printf("datum: %2d.%2d.%4d - cislo: %04X hexa\n",
          dnes.den, dnes.mesic, dnes.rok + 1980, dnes);

  dnes.mesic = 12;
  printf("datum: %2d.%2d.%4d - cislo: %04X hexa\n",
          dnes.den, dnes.mesic, dnes.rok + 1980, dnes);

  dnes.rok = 2003 - 1980;
  printf("datum: %2d.%2d.%4d - cislo: %04X hexa\n",
          dnes.den, dnes.mesic, dnes.rok + 1980, dnes);

  zitra.den = dnes.den + 1;
  zitra.mesic = dnes.mesic;
  zitra.rok = dnes.rok;
  printf("datum: %2d.%2d.%4d - cislo: %04X hexa\n",
          zitra.den, zitra.mesic, zitra.rok + 1980, zitra);
  return 0;
}

