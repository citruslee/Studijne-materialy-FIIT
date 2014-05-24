/*
 * den-v-tydnu.c    v.2.0
 *
 * Zjisteni dne v tydnu
 * ====================
 */

#include <stdio.h>
#include <time.h>

int main(int argc, char **argv)
{
  struct tm den;
  char *dny[] = {"Ne", "Po", "Ut", "St", "Ct", "Pa", "So"};

  if (argc == 1) {
    printf("Pouziti: den-v-tydnu den mesic rok (20 11 2003)");
    return 1;
  }

  den.tm_sec = 0;
  den.tm_min = 0;
  den.tm_hour = 12;
  den.tm_mday = atoi(argv[1]);
  den.tm_mon = atoi(argv[2]) - 1;
  den.tm_year = atoi(argv[3]) - 1900;
  mktime(&den);
  printf("%d.%d.%d byl den: %s\n",
           den.tm_mday, den.tm_mon + 1, 1900 + den.tm_year,
           dny[den.tm_wday]);

  return 0;
}

