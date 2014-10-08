/*
 * s340.c    v.2.0
 *
 * Nahodna cisla
 * =============
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void)
{
  int i;
  srand((unsigned int) time(NULL));
  printf("\nDeset nahodnych cisel od 0 do 99\n");
  for (i = 0;  i < 10;  i++)
    printf("%2d  ", rand() % 100);

  return 0;
}
