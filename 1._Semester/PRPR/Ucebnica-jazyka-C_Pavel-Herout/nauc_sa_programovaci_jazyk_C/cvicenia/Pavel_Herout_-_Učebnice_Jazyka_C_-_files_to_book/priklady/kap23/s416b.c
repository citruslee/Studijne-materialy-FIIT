/*
 * s416b.c    v.2.0
 *
 * Slozeny literal
 * ===============
 */

#include <stdio.h>

int main(void)
{
  int i;
  int *kpole = (const int[]) {1, 2, 4, 8, 16};

  for (i = 0;  i < 5;  i++) {
    printf("%d, ", kpole[i]);
  }
/*  kpole[0] = 3;    /* chyba */
  printf("\n%d", kpole[0]);

  return 0;
}

