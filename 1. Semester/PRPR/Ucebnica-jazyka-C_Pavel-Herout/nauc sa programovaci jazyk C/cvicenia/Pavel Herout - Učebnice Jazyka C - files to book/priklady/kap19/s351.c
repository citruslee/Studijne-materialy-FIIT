/*
 * s351.c    v.2.0
 *
 * Prace s bloky pameti
 * ====================
 */

#include <stdio.h>
#include <string.h>

#define DELKA  1000

int main(void)
{
  int a[DELKA], b[DELKA];
  int i, *p_i;

  memset((void *)a, 0, (size_t) (DELKA * sizeof(int)));
  printf("memset: a[%d] = %d\n", DELKA / 2, a[DELKA / 2]);
  a[DELKA / 2] = 1;

  p_i = (int *) memchr((void *) a, 1,
                       (size_t) (DELKA * sizeof(int)));
  printf("memchr: i = %u\n", p_i - a);

  memcpy((void *)b, (void *)a, (size_t) (DELKA * sizeof(int)));
  printf("memcpy: b[%d] = %d\n", DELKA / 2, b[DELKA / 2]);
  for (i = 1;  i < 9;  i++)
    a[i] = i - 1;
  for (i = 0;  i < 9;  i++)
    printf("a[%d]=%d ", i, a[i]);

  printf("\nmemmove:\n");
  memmove((void *) &a[0], (void *) &a[1],
          (size_t) (9 * sizeof(int)));
  for (i = 0;  i < 9;  i++)
    printf("a[%d]=%d ", i, a[i]);
  return 0;
}

