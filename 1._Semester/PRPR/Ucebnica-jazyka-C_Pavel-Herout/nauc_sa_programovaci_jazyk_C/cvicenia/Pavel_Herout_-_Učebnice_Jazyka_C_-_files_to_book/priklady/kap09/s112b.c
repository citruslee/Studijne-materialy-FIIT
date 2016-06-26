/*
 * s112b.c    v.2.0
 *
 * Funkce bez parametru s pouzitim void
 * ====================================
 */

#include <stdio.h>

int secti(void)
{
  int a, b;

  scanf("%d %d", &a, &b);
  return (a + b);
}

int main()
{
  printf("Zadej dve cela cisla: ");
  printf("Sectena cisla = %d\n", secti());
  return 0;
}

