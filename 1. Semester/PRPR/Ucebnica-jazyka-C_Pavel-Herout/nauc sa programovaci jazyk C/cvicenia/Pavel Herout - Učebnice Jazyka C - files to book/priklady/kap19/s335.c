/*
 * s335.c    v.2.0
 *
 * Signaly v UNIXu a navraty z obsluhy
 * ===================================
 */

/*
 POZOR - prekladat jen pod systemem UNIX.
*/

#include <stdio.h>
#include <signal.h>
#include <setjmp.h>

#define VYNECH  10000000 /* znak se vypisuje jednou za VYNECH */

jmp_buf navrat;
void (* stara_adresa)(int);

char vypisovany_znak = 'a';
int skoncit_program = 0;

void obsluha_signalu(int nevyuzity_parametr)
{
  vypisovany_znak++;

  if (skoncit_program  == 1)
    longjmp(navrat, 1);
}

int main(void)
{
  unsigned long int i = 0;

  printf("Zadej zpusob chovani po navratu ze signalu\n"
         "0=pokracovat, 1=skoncit program: ");
  scanf("%d", &skoncit_program);
 
  /* zavedeni nove adresy obsluhy SIGQUIT */
  stara_adresa = signal(SIGQUIT, obsluha_signalu);

  printf("\nZadej prikaz: kill -%d %d\n", SIGQUIT, getpid());

  if (setjmp(navrat) == 0) {
    while (1) {
      if (++i % VYNECH == 0) {
        putchar(vypisovany_znak);
        fflush(stdout);
      }
    }
  }
  else {
    printf("\nProgram byl ukoncen signalem...\n");
  }

  /* obnoveni puvodni adresy obsluhy SIGQUIT */
  signal(SIGQUIT, stara_adresa);
  return 0;
}

