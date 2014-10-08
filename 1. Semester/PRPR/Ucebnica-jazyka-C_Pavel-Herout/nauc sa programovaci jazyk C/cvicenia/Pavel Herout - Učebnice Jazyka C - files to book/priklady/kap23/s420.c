/*
 * s420.c    v.2.0
 *
 * Inline funkce
 * =============
 */

#include <stdio.h>

inline int faktorial(int n)
{
  int f = 1;

  for (; n > 1;  n--)
    f *= n;

  return f;
}

int main(void)
{
  printf("%d! = %d\n", 5, faktorial(5));
  return 0;
}

