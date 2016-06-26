/*
 * hlavni.c    v.2.0
 *
 * Externi deklarace v oddelenych souborech
 * ========================================
 */

/* zacatek souboru hlavni.c */
#include <stdio.h>

extern int x;            /* deklarace */
extern int fun(void);    /* nebo jen  extern int fun()
                            nebo jen  int fun(void)
                            nebo jen  int fun()         */
double f;                /* definice  */

int main(void)
{
  x = 3;
  f = 3.5;
  printf("%d\n", fun());
  return 0;
}
/* konec souboru hlavni.c */
