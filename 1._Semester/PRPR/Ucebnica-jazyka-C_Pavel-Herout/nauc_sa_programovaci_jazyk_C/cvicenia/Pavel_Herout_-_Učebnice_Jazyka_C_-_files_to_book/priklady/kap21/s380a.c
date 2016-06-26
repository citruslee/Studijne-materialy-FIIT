/*
 * s380a.c    v.2.0
 *
 * Dvoji moznost potlaceni ladicich vypisu
 * =======================================
 */

#include <stdio.h>
#include <ctype.h>

#define DBG

int main(void)
{
#ifdef DBG
  int c;

  fprintf(stderr, "Chcete ladici vypisy ? [A/N]: ");
  c = toupper(getchar());
  if (c == 'N')
    fclose(stderr);
#endif
  printf("printf - ahoj\n");
  fprintf(stdout, "fprintf - stdout ahoj\n");
#ifdef DBG
  fprintf(stderr, "fprintf - stderr ahoj\n");
#endif

  return 0;
}

