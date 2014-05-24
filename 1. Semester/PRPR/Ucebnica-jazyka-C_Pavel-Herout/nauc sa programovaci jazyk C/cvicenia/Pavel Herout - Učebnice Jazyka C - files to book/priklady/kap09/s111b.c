/*
 * s111b.c   v.2.0
 *
 * Funkce bez parametru
 * ====================
 */

#include <stdio.h>

int secti()
{
  int a, b;

  scanf("%d %d", &a, &b);
  return (a + b);
}

int main()
{
  int j;

  printf("Zadej dve cela cisla: ");
  j = secti();
  printf("Sectena cisla = %d\n", j);
  return 0;
}

