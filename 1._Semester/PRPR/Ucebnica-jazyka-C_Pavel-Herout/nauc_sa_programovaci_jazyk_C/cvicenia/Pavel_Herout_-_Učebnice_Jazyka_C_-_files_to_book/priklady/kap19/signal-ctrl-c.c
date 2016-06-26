/*
 * signal-ctrl-c.c    v.2.0
 *
 * Jak zajistit svoji vlastni reakci na nasilne ukonceni programu
 * ==============================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void obsluha_signalu(int nevyuzity_parametr)
{
  printf("Stisknuto Ctrl-C\n");
  exit(1);
}

int main(void)
{
  printf("Pro skonceni programu stiskni Ctrl-C\n");
  signal(SIGINT, obsluha_signalu);

  while (1)
    ;

  return 0;
}
