/*
 * s357b.c    v.2.0
 *
 * Pouziti funkce asctime()
 * ========================
 */

#include <stdio.h>
#include <time.h>

int main(void)
{
  time_t t;

  time(&t);
  printf("%s\n", asctime(localtime(&t)));
  printf("%s\n", ctime(&t));
  return 0;
}

