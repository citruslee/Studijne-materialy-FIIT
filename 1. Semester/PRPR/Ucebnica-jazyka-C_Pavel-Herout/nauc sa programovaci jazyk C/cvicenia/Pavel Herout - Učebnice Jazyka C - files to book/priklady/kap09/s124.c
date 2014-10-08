/*
 * s124.c    v.2.0
 *
 * Pouziti promenne typu register
 * ==============================
 */

#include <stdio.h>

void nasobilka(register int k)
{
  register int i;

  for (i = 1;  i <= 10;  i++)
    printf("%2d x %d = %2d\n", i, k, i * k);
}

int main(void)
{
  printf("Mala nasobilka 7\n");
  nasobilka(7);
  return 0;
}

