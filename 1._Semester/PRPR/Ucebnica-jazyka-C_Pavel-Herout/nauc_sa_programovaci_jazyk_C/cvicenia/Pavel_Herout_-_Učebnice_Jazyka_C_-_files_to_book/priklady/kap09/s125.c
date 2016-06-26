/*
 * s125.c    v.2.0
 *
 * Pouziti modifikatoru const
 * ==========================
 */

#include <stdio.h>

int main(void)
{
  const float pi = 3.14159;  /* definice a inicializace */
  const max = 100;           /* typ int je implicitni */
  int pole[max];
  const char *p_c = "Ahoj";
  char *const p_d = "Nazdar";

  pi = 3.14;                 /* chybne */
  p_c = "Cao";
  p_d = "Cao";               /* chybne */

  printf("pi  = %f\n", pi);
  printf("p_c = %s\n", p_c);
  printf("p_d = %s\n", p_d);
  return 0;
}

