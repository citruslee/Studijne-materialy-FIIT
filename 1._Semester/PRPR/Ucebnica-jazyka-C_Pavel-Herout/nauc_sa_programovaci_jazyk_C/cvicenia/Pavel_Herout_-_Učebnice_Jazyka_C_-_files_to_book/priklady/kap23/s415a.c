/*
 * s415a.c    v.2.0
 *
 * Inicializace pouze nekterych prvku pole
 * =======================================
 */

#include <stdio.h>

int main(void)
{
  int i;
  int pole[10] = { 1, 2, [8] = 128 };

  for (i = 0;  i < 10;  i++) {
    printf("%d, ", pole[i]);
  }

  return 0;
}

