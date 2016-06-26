/*
 * s198b.c    v.2.0
 *
 * Nacteni a tisk dynamickeho retezce
 * ==================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  char *str;

  if ((str = (char *) malloc(11)) == NULL) {
    printf("Malo pameti\n");
    return;
  }
  printf("Zadej retezec: ");
  scanf("%s", str);
  printf("Retezec je: %s\n", str);
  free((void *) str);
  return 0;
}

