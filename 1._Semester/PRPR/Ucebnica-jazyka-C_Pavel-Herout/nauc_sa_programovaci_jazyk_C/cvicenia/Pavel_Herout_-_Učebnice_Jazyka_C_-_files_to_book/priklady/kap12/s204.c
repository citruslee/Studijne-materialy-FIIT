/*
 * s204.c    v.2.0
 *
 * Generovani jmen souboru
 * =======================
 */

#include <stdio.h>

int main(void)
{
  int i;
  char jmeno[50];

  for (i = 1;  i < 20;  i++) {
    sprintf(jmeno, "obr%02d.jpg", i);
    printf("%s\n", jmeno);
  }

  return 0;
}

