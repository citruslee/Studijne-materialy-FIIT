/*
 * s122.c    v.2.0
 *
 * Pouziti lokalni staticke promenne
 * =================================
 */

#include <stdio.h>

void f(void)
{
  int x = 2;
  static int i = 0;

  printf("f byla volana %d-krat, x = %d\n", i, x);
  i++;
  x++;
}

int main(void)
{
  int j;

  for (j = 0;  j < 3;  j++)
    f();
  return 0;
}

