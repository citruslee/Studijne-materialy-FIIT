/*
 * s380b.c    v.2.0
 *
 * Podmineny preklad vyuzivajici hodnotu symbolicke konstanty
 * ==========================================================
 */

#include <stdio.h>
#include <ctype.h>

#define DBG
#define JAK 1   /* 1 = hexadecimalne, 2 = oktalove */

int main(void)
{
  int delenec = 5,
      delitel = 0;

#if defined(DBG)
  int c;

  fprintf(stderr, "Chcete ladici vypisy ? [A/N]: ");
  c = toupper(getchar());
  if (c == 'N')
    fclose(stderr);
#endif

#if defined(DBG)  &&  JAK == 1
  fprintf(stderr, "stderr: delitel= %x -hexa\n", delitel);

#elif defined(DBG)  &&  JAK == 2
  fprintf(stderr, "stderr: delitel= %o -octal\n", delitel);

#else
  fprintf(stderr, "stderr: 'Bez ladicich vypisu'\n");
#endif

  printf("stdout: celociselny podil = %d\n", delenec / delitel);

  return 0;
}

