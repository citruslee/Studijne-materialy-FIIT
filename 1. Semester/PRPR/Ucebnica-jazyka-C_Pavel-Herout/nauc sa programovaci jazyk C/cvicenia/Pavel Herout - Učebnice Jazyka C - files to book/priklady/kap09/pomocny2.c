/*
 * pomocny2.c    v.2.0
 *
 * Externi deklarace a globalni promenna typu static
 * =================================================
 */

/* zacatek souboru pomocny2.c */
/* static */ int x;          /* definice  */
extern double f;       /* deklarace */

static double fun(double x)
{
  return x;
}

int funkce(void)
{
  return ((int) fun(f) + x);
}

/* konec souboru pomocny2.c */
