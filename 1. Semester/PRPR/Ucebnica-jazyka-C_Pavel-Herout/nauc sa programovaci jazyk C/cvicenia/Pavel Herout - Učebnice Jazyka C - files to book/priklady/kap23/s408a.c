/*
 * s408a.c    v.2.0
 *
 * Definice kdekoliv v kodu
 * ========================
 */

#include <stdio.h>

int main(void)
{
  int pole[10];

  for (int i = 0;  i < 10;  i++) {
    pole[i] = i + 1;
    int j = pole[i];
    printf("%d, ", j);
  }

  return 0;
}
