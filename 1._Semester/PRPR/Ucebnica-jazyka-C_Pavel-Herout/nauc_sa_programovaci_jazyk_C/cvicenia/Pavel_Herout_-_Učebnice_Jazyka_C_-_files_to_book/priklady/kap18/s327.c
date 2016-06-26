/*
 * s327.c    v.2.0
 *
 * Zmena chybovych hlaseni
 * =======================
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(void)
{
  errno = ENOENT;   /* symbolicka konstanta z <errno.h> */
  perror("Anglicky");

  sys_errlist[ENOENT] = "Tento soubor nebo adresar neexistuje";

  errno = ENOENT;
  perror("Cesky");
  printf("CHYBA - %s", strerror(ENOENT));
  return 0;
}

