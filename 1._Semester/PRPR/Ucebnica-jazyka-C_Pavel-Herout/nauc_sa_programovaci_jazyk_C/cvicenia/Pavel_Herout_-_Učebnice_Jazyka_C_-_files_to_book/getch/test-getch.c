/* test-get.c
 *
 * Testovaci priklad ke knihovne getch.c (c) Brozik
 * ================================================
 *
 * P.Herout & V.Brozik  IX.1998
 */

#include <stdio.h>
#include <ctype.h>

#ifndef unix
#ifdef __unix__
#define unix __unix__
#elif defined (__unix)
#define unix __unix
#endif /* __unix__ */
#endif /* unix */
 
#ifdef unix
#  include "getch.h"
#  include "getch.c"		/* aby nemusel byt oddeleny preklad */
#else
#  include <conio.h>
#endif

int main(void)
{
  int c, i, j, k;

#ifdef unix
  getch_init(GETCH_SIGINT);	/* inicializace */
#endif

  printf("\nTest kbhit()\n"
         "Stale vypisuje cisla, pokud stisknete klavesu, vypise '***'\n"
         "Konec testu - stisk 'Q' (quit)\n");
  i = 0;
  while (1) {
    if (kbhit() != 0) {
      c = getch();
      if (toupper(c) == 'Q') {
        break;
      }
      printf("\n ***\n");
      fflush(stdout);
    }
    i++;
    j = printf("%d", i);
    /* navrat za zacatek radky */
    for (k = 1;  k <= j;  k++) {
      putchar('\b');
    }
    fflush(stdout);
  }

  printf("\n\nTest getch() - cte, ale neechuje\n"
         "Ceka na vstup (zadavat bez <Enter>), ktery opise\n"
         "Konec testu - stisk 'Q' (quit)\n");
  while (1) {
    printf("Zadej znak: ");
    fflush(stdout);
    c = getch();
    if (toupper(c) == 'Q') {
      break;
    }
    printf("\tgetch() precetl: %c\n", c);
  }

  printf("\n\nTest getche() - cte a echuje\n"
         "Ceka na vstup (zadavat bez <Enter>), ktery opise\n"
         "Konec testu - stisk 'Q' (quit)\n");
  while (1) {
    printf("Zadej znak: ");
    fflush(stdout);
    c = getche();
    if (toupper(c) == 'Q') {
      break;
    }
    printf("\tgetche() precetl: %c\n", c);
  }
  printf("\n\n");
  
#ifdef unix
  getch_end();			/* uklid */
#endif

  return 0;
}



