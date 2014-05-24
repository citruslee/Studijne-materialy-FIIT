/*
 * s182.c    v.2.0
 *
 * Pole menici svoji velikost
 * ==========================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  int *x;                         /* pole */
  int pocet = 10;                 /* velikost pole */
  int *p_pom1, *p_pom2, *p_nove;  /* pomocne pointery */
  int i;

  /* pocatecni alokace pole */
  x = (int *) malloc(pocet * sizeof(int));
  if (x == NULL) {
    printf("Malo pameti\n");
    return 1;
  }

  /* prace s polem */
  for (i = 0;  i < pocet;  i++) {
    x[i] = i;
    printf("%2d ", x[i]);
  }

  /* odradkovani */
  putchar('\n');

  /* alokace vetsiho pole */
  p_nove = (int *) malloc((pocet + 10) * sizeof(int));
  if (p_nove == NULL) {
    printf("Malo pameti\n");
    return 1;
  }

  p_pom1 = x;
  p_pom2 = p_nove;
  while (p_pom1 < x + pocet)      /* kopirovani stareho pole */
    *p_pom2++ = *p_pom1++;        /* na novou adresu */
  pocet += 10;
  free((void *) x);               /* uvolneni stareho pole */
  x = p_nove;

  /* prace s vetsim polem */
  for (i = 0;  i < pocet;  i++) {
    x[i] = i;
    printf("%2d ", x[i]);
  }
  return 0;
}

