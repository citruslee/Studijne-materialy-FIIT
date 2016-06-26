/*
 * s356.c    v.2.0
 *
 * Pouziti funkce time()
 * =====================
 */

#include <stdio.h>
#include <time.h>

int main(void)
{
  time_t pocet_sec, n_sec;

  pocet_sec = time(&n_sec);
  printf("1. pocet sekund = %lu\n", pocet_sec);
  printf("1. pocet sekund = %lu\n", n_sec);

  pocet_sec = time(&pocet_sec);
  printf("2. pocet sekund = %lu\n", pocet_sec);

  pocet_sec = time(NULL);
  printf("3. pocet sekund = %lu\n", pocet_sec);

  return 0;
}

