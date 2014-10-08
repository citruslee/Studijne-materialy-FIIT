/*
 * s217.c    v.2.0
 *
 * Ulozeni dvourozmerneho pole v pameti
 * ====================================
 */

#include <stdio.h>

int main(void)
{
  int x[2][3];
  int i, j;

  for (i = 0;  i < 2;  i++)       /* pro kazdou radku */
    for (j = 0;  j < 3;  j++)     /* pro kazdy sloupec */
      x[i][j] = i + j;

  for (i = 0;  i < 2;  i++) {
    printf("mapa pameti pro %d. radku:\n", i);
    for (j = 0;  j < 3;  j++)
      printf("\t sloupec %d \t adresa %p \t hodnota %d\n",
             j, (x[i] + j), x[i][j]);
    putchar('\n');
  }

  return 0;
}
