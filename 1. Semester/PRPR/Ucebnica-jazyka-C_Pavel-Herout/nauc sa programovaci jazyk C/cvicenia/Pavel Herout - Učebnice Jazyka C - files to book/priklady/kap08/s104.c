/*
 * s104.c    v.2.0
 *
 * Netrivialni rizeni prekladu
 * ===========================
 *
 * vyuziti prikazu defined, elif a error
 */

#define ZAKLADNI
/* #define STREDNI */

#define DEBUG

#if defined(ZAKLADNI)  &&  defined(DEBUG)
  #define VERZE_LADENI    1
#elif defined(STREDNI)  &&  defined(DEBUG)
  #define VERZE_LADENI    2
#elif !defined(DEBUG)
  #error Pozor, ladici verzi neni mozne pripravit!
#else
  #define VERZE_LADENI    3
#endif

#include <stdio.h>

int main()
{
  printf("Verze ladeni = %d\n", VERZE_LADENI);
  return 0;
}

