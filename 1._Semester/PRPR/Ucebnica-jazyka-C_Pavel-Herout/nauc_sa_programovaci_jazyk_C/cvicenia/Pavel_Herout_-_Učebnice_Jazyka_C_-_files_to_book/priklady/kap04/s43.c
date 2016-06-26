/*
 * s43.c    v.2.0
 *
 * Formatove konverze u funkce printf()
 * ====================================
 */

#include <stdio.h>

int main()
{
  char  c = 'A';
  int   hodiny, minuty, pocet;
  float cena_piva;

  printf("Znak '%c' ma ASCII kod %d (%XH)\n", c, c, c);

  printf("Znak '%c' ma ASCII kod %d (%XH)\n", '*', '*', '*');

  hodiny = 1; minuty = 12;
  printf("Je presne %2d:%2d\n", hodiny, minuty);

  hodiny = 13; minuty = 3;
  printf("Je presne %2d:%2d\n", hodiny, minuty);

  pocet = 8;
  cena_piva = 1.70;
  printf("Za pivo jsme utratili: %6.2f Kcs.\n", pocet * cena_piva);

  printf("Kolik stalo %s pivo?\n", "jedno");
  return 0;
}
