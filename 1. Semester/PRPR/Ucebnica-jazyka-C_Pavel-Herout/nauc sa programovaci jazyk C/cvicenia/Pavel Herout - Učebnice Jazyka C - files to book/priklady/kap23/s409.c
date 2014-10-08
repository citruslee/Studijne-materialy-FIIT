/*
 * s409.c    v.2.0
 *
 * Logicke typy a hodnoty
 * ======================
 */

#include <stdio.h>
#include <stdbool.h>

int main(void)
{
  _Bool b = true;
  bool c;

  if (b == true)
    c = false;

  printf("b = %d, c = %d\n", b, c);
  b = 1 + 2;
  c = 0.0 / 3.14;
  printf("b = %d, c = %d\n", b, c);

  return 0;
}


