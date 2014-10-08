/*
 * s357a.c    v.2.0
 *
 * Pouziti funkce localtime()
 * ==========================
 */

#include <stdio.h>
#include <time.h>

int main(void)
{
  struct tm   tm_promenna, *p_tm;
  time_t      cas;

  time(&cas);
  tm_promenna = *localtime(&cas);  /* prirazeni struktur  */
  if (tm_promenna.tm_min == 2)
    printf("Pocet minut je 2\n");
  else
    printf("Pocet minut neni 2 (%d)\n", tm_promenna.tm_min);

  p_tm = localtime(&cas);          /* prirazeni ukazatelu */
  if (p_tm->tm_min == 2)
    printf("Pocet minut je 2\n");
  else
    printf("Pocet minut neni 2 (%d)\n", p_tm->tm_min);

  return 0;
}
