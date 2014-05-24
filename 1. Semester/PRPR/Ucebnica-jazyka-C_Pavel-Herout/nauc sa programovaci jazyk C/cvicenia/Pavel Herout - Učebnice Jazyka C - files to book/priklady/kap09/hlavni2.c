/*
 * hlavni2.c    v.2.0
 *
 * Externi deklarace a globalni promenna typu static
 * =================================================
 */

/* zacatek souboru hlavni2.c */
#include <stdio.h>

extern int x;             /* deklarace */
extern int funkce(void);  /* funkcni prototyp */
double f;                 /* definice  */

static void fun(void)
{
  printf("%d\n", funkce());
}

int main(void)
{
  x = 3;
  f = 3.5;
  fun();
  return 0;
}

/* konec souboru hlavni2.c */
