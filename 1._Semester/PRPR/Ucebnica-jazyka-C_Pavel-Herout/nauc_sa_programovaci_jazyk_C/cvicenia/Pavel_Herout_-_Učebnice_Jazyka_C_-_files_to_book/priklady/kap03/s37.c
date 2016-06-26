/*
 * s37.c    v.2.0
 *
 * Inkrement a dekrement
 * =====================
 */

#include <stdio.h>

int main()
{
  int i = 5,
      j = 1,
      k;

  i++;
  printf("i = %d, j = %d, k = %d\n", i, j, k);
  j = ++i;
  printf("i = %d, j = %d, k = %d\n", i, j, k);
  j = i++;
  printf("i = %d, j = %d, k = %d\n", i, j, k);
  k = --j + 2;
  printf("i = %d, j = %d, k = %d\n", i, j, k);
  return 0;
}
