/*
 * s411.c    v.2.0
 *
 * Presna sirka datovych typu
 * ==========================
 */

#include <stdio.h>
#include <sys/types.h>

int main(void)
{
  int32_t i32 = 0x7FFFFFFF;

  printf("format %%d  = %d\n", i32);
  printf("format %%ld = %ld\n", i32);

  return 0;
}

