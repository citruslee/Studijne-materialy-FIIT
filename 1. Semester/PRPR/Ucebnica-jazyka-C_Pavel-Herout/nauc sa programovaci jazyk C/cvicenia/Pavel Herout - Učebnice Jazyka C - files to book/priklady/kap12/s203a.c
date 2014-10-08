/*
 * s203a.c    v.2.0
 *
 * Pouziti funkci sprintf() a sscanf()
 * ===================================
 */

#include <stdio.h>

int main(void)
{
  int i;
  char s1[5], s2[10];

  printf("Zadej 4 hexa cislice: ");
  scanf("%s", s1);
  sscanf(s1, "%x", &i);
  sprintf(s2, "%o", i);
  printf("Vysledek v osmickove soustave: %s\n", s2);
  return 0;
}

