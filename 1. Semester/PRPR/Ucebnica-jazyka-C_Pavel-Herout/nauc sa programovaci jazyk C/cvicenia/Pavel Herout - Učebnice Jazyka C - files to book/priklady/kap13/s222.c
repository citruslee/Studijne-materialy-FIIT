/*
 * s222.c    v.2.0
 *
 * Ukazka funkce pro alokovani dvourozmerneho pole s int prvky
 * ===========================================================
 */

#include <stdio.h>
#include <stdlib.h>

int **vytvor_pole(int radky, int sloupce)
{
  int **p_p_x, i;

  p_p_x = (int **) malloc(radky * sizeof(int *));
  for (i = 0;  i < radky;  i++)
    p_p_x[i] = (int *) malloc(sloupce * sizeof(int));

  return p_p_x;
}

void uvolni_pole(int **p_p_x, int radky)
{
  int i;

  for (i = 0;  i < radky;  i++)
    free((void *) p_p_x[i]);

  free((void *) p_p_x);
}

int main(void)
{
  int **a, **b;

  a = vytvor_pole(3, 11);
  b = vytvor_pole(8, 4);

  a[1][2] = 5;
  printf("Prvek ma hodnotu: %d\n", a[1][2]);

  b[7][3] = 1;
  printf("Prvek ma hodnotu: %d\n", b[7][3]);

  uvolni_pole(a, 3);
  uvolni_pole(b, 8);
  return 0;
}

