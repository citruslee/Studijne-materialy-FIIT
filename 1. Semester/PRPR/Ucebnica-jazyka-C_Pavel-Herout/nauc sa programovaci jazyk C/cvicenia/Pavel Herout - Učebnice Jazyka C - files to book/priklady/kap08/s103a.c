/*
 * s103a.c    v.2.0
 *
 * Podmineny preklad rizeny definici makra
 * =======================================
 */


#include <stdio.h>

/* #define WINDOWS */

#ifdef WINDOWS
  #define JMENO   "D:\\data\\senzor.txt"
#else
  #define JMENO   "/data/senzor.txt"
#endif

int main()
{
  FILE *fr;

  /* prace se souborem nezavisla na operacnim systemu */
  if ((fr = fopen(JMENO, "r")) == NULL) {
    printf("Soubor '%s' se nepodarilo otevrit\n", JMENO);
    return 1;
  }

  /* zde by se zpracovaval soubor */

  fclose(fr);
  return 0;
}

