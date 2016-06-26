/*
 * nazdar.c
 */

#include <stdio.h>

#include "nazdar.h"
#include "cao.h"
#include "max.h"

int n = 4;

void nazdar(int n)
{
  int i;

  for (i = 0;  i < n  &&  i < MAX;  i++) {
    printf("%d: %s - ", i, NAZDAR);
    cao(i);
  }
}
