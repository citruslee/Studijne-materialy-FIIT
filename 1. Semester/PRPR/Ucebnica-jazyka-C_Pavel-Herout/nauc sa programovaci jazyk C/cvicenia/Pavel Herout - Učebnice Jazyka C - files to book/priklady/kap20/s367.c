/*
 * s367.c    v.2.0
 *
 * Chybovy vypis pomoci vprintf(), ...
 * ===================================
 */

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

/* tiskne chybove hlaseni na stdout, stderr
 * a zapisuje ho do retezu str */
void chyba(char *str, char *format, ...)
{
  va_list  argumenty;    /* pomocna promenna */
  char     *p_pom;

  /* vyuziti vprintf() - vystup na obrazovku - stdout */
  printf("\nChyba - obrazovka: ");
  va_start(argumenty, format);
  vprintf(format, argumenty);
  va_end(argumenty);

  /* opakovane pouziti promennych parametru */
  /* vyuziti vfprintf() - vystup na stderr */
  fprintf(stderr, "\nChyba - stderr: ");
  va_start(argumenty, format);
  vfprintf(stderr, format, argumenty);
  va_end(argumenty);

  /* opakovane pouziti promennych parametru */
  /* vyuziti vsprintf() - vystup do retezce */
  p_pom = strcpy(str, "\nChyba - string: ");
  p_pom += strlen(str);
  va_start(argumenty, format);
  vsprintf(p_pom, format, argumenty);
  va_end(argumenty);
}

int main(void)
{
  char radka[1000];
  int i = 5;
  float f = 3.14;

  /* zadne promenne parametry */
  chyba(radka, "Zadna chyba\n");
  puts(radka);

  /* dva promenne parametry */
  chyba(radka, "int = %d, float = %f\n", i, f);
  puts(radka);

  /* ctyri promenne parametry */
  chyba(radka, "int = %d, float = %f, %d, %f\n", i, f, i, f);
  puts(radka);

  return 0;
}

