/*
 * s225a.c    v.2.0
 *
 * Inicializace pole a zjisteni jeho velikosti
 * ===========================================
 */

#include <stdio.h>

int globalni[] = { 1, 2, 3, 4, 5 };
int n_glob = sizeof(globalni) / sizeof(int);

int main(void)
{
  char *lokalni[] = { "jedna", "dva", "tri", "ctyri" };
  int n_lok = sizeof(lokalni) / sizeof(char *);

  int i;

  printf("globalni = %d: ", n_glob);
  for (i = 0;  i < n_glob;  i++)
    printf("%d, ", globalni[i]);

  printf("\nlokalni = %d: ", n_lok);
  for (i = 0;  i < n_lok;  i++)
    printf("%s, ", lokalni[i]);

  return 0;
}

