/*
 * s328.c    v.2.0
 *
 * Prace s promennymi prostredi
 * ============================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
  printf("%s\n", getenv("PATH"));
  return 0;   
}

