/*
 * s111a.c    v.2.0
 *
 * Funkce vracejici maximum ze dvou parametru
 * ==========================================
 */

#include <stdio.h>

int max(int a, int b)
{
  return (a > b ? a : b);
}

int main()
{
  int i = 3,
      j = 7;

  printf("Z cisel %d a %d je vetsi %d\n", i, j, max(i, j));
  return 0;
}

