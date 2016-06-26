/*
 * s371.c    v.2.0
 *
 * Seznam parametru je ukoncen definovanou hodnotou
 * ================================================
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* seznam retezcu musi byt ukoncen parametrem NULL */
void spoj_retezce(char *cilovy, ...)
{
  va_list  argumenty;
  char *str;

  cilovy[0] = '\0';

  va_start(argumenty, cilovy);
  while ((str = va_arg(argumenty, char *)) != NULL)
    strcat(cilovy, str);
  va_end(argumenty);
}

int main(void)
{
  char radka[80];

  spoj_retezce(radka, "ahoj", NULL);
  puts(radka);
  spoj_retezce(radka, "ahoj ", "programatori ", NULL);
  puts(radka);
  spoj_retezce(radka, NULL);
  puts(radka);
  spoj_retezce(radka, "ahoj ", "programatori ", "v C", NULL);
  puts(radka);
  spoj_retezce(radka, "Funkce ", "s ", "promennym ",
               "poctem parametru", NULL);
  puts(radka);
  return 0;
}

