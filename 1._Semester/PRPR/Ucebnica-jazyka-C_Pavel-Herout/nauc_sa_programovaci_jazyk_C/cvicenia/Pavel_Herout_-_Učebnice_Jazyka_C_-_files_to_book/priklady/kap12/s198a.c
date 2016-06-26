/*
 * s198a.c    v.2.0
 *
 * Nacteni a tisk statickeho retezce
 * =================================
 */

#include <stdio.h>

int main(void)
{
  char str[11];

  printf("Zadej retezec: ");
  scanf("%s", str);
  printf("Retezec je: %s\n", str);
  return 0;
}

