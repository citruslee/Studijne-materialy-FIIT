/*
 * kru_main.c    ver. 2.0
 *
 * Program pro vypocty obvodu a obsahu kruznice
 * ============================================
 *
 * P. Herout,  rijen 2003
 *
 */

/* systemove hlavickove soubory */
#include <stdio.h>

/* vlastni hlavickove soubory */
#include "kru_main.h"   /* natazeni symbolickych konstant,
                           funkcnich prototypu globalnich funkci
                           a globalnich typu vlastniho
                           modulu */
#include "kru_io.h"     /* natazeni symbolickych konstant,
                           funkcnich prototypu globalnich funkci
                           a globalnich typu spolupracujiciho
                           modulu */

/* definice globalnich promennych */
double obvod;

/* lokalni definice symbolickych konstant */
#define PI    3.14

/*  lokalni definice novych typu */
  /*  zde nejsou zadne typedef pouzity
   *  pokud by byly pouzity, vypadaly by napr.:
   *    typedef int MOJE_INT;
   */

/* definice statickych globalnich promennych */
static double polomer;
static double obsah;

/* uplne funkcni prototypy lokalnich funkci */
static void vyp_obsahu(double polomer);
static double vyp_obvodu(void);
static void vypocet(void);

/* funkce main() */
int main(void)
{
  polomer = vstup_dat();

  if (polomer == CHYBA_DAT) {
    /* Chybne zadana vstupni data - zaporna hodnota */
    printf("Polomer kruznice chybne zadan\n");
    return 1;
  }
  else {
    vypocet();
    vystup_dat(obsah);
  }
  return 0;
}

/* definice lokalnich funkci */
static void vyp_obsahu(double polomer)
{
  obsah = PI * polomer * polomer;
}

static double vyp_obvodu(void)
{
  return (PI * vyp_prumeru(polomer));
}

static void vypocet(void)
{
  obvod = vyp_obvodu();
  vyp_obsahu(polomer);
}

/* definice globalnich funkci */
double vyp_prumeru(double polomer)
{
  return (2 * polomer);
}

