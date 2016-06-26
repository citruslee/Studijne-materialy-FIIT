/*
 * s341.c    v.2.0
 *
 * Akce po skonceni funkce main()
 * ==============================
 */

#include <stdio.h>
#include <stdlib.h>

void exit_fn1(void) {  printf("1. exit_funkce\n");  }

void exit_fn2(void) {  printf("2. exit_funkce\n");  }

int main(void)
{
  printf("Zacatek programu a registrace exit_fn funkci\n");
  atexit(exit_fn1);
  atexit(exit_fn2);
  printf("Konec programu\n");
  return 0;
}

