/*
 * s333.c    v.2.0
 *
 * Dlouhe skoky
 * ============
 */

#include <stdio.h>
#include <setjmp.h>

void chyba(void);          /* funkcni prototyp  */
jmp_buf hlavni_smycka;     /* globalni promenna */

int main(void)
{
  int i, j;

  printf("Zacatek programu\n");

  if (setjmp(hlavni_smycka) != 0)
    printf("Restart po chybe ...\n");

  while (1) {
    printf("Zadej dve cisla (0 0 = konec): ");
    scanf("%d %d", &i, &j);
    if (i == 0)
      break;
    if (j != 0)
      printf("%d / %d = %d\n", i, j, i / j);
    else
      chyba();
  }
  return 0;
}

void chyba(void)
{
  printf("Chyba - nulovy delitel\n\n");
  longjmp(hlavni_smycka, 1);
}

