/*
 * razeni-rychlosti.c
 *
 * Porovnavani rychlosti razeni
 * ============================
 *
 * (c) P.Herout - 12.2002
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <sys/unistd.h>

#define MAX_JMENO 500
#define OPAKOVANI 5

typedef struct {
  int vek;
  char jmeno[MAX_JMENO];
} CLOVEK;

int pocet_prvku;

CLOVEK *pole = NULL;
CLOVEK **p_pom_pole = NULL;

void nahodna_inicializace(void);
int priprav_pole(void);
void vypis_pole(void);
int sort_delsi(const void *p_a, const void *p_b);
int sort_kratsi(register const void *p_a, register const void *p_b);
int sort_nejkratsi(register const void *p_a, register const void *p_b);

int main(void)
{
  int i;
  double cas, prum;
  FILE *fr;

  /* pro mereni casu */
  struct tms casova_struktura;
  clock_t program_z, program_k;

  while (priprav_pole() != 0) {
    prum = 0.0;
    for (i = 1;  i <= OPAKOVANI;  i++) {
      nahodna_inicializace();
      vypis_pole();

      (void) times(&casova_struktura);
      program_z = casova_struktura.tms_utime;
/*
      qsort((void *)pole, pocet_prvku, sizeof(CLOVEK), sort_delsi);
*/
/*
      qsort((void *)pole, pocet_prvku, sizeof(CLOVEK), sort_kratsi);
*/
      qsort((void *)p_pom_pole, pocet_prvku, sizeof(CLOVEK *), sort_nejkratsi);

      (void) times(&casova_struktura);
      program_k = casova_struktura.tms_utime;
      cas = ((program_k - program_z) / (double) sysconf(_SC_CLK_TCK)) * 1000;
      printf("%d.=%.0f, ", i, cas);
      fflush(stdout);
      prum += cas;
      vypis_pole();
    }
    prum /= OPAKOVANI;
    printf("\n%10d: %.0f [msec]\n", pocet_prvku, prum);
  }

  return 0;
}

void nahodna_inicializace(void)
{
  int i, j;

  for (i = 0;  i < pocet_prvku;  i++) {
    pole[i].vek = rand() % 100;
    for (j = 0;  j < MAX_JMENO - 1;  j++) {
      pole[i].jmeno[j] = rand() % 26 + 'a';
    }
    pole[i].jmeno[MAX_JMENO - 1] = '\0';
  }
}

int priprav_pole(void)
{
  int i;

  printf("Zadej pocet prvku pole (0 = konec): ");
  scanf("%d", &pocet_prvku);

  if (pole != NULL) {
    free((void *) pole);   /* uvolneni z predchoziho behu */
  }
  if (p_pom_pole != NULL) {
    free((void *) p_pom_pole);   /* uvolneni z predchoziho behu */
  }

  pole = (CLOVEK *) malloc(pocet_prvku * sizeof(CLOVEK));
  if (pole == NULL) {
    printf("Malo pameti pro pole\n");
    exit(1);
  }

  p_pom_pole = (CLOVEK **) malloc(pocet_prvku * sizeof(CLOVEK *));
  if (p_pom_pole == NULL) {
    printf("Malo pameti pro pomocne pole\n");
    exit(1);
  }

  for (i = 0;  i < pocet_prvku;  i++) {
    p_pom_pole[i] = &pole[i];
  }

  return pocet_prvku;
}

void vypis_pole(void)
{
  int i;

  if (pocet_prvku > 10)
    return;                /* moc dlouhe - nic netisknout */

  for (i = 0;  i < pocet_prvku;  i++) {
/*    printf("%2d, %s\n", pole[i].vek, pole[i].jmeno);
*/
    printf("%2d, %s\n", p_pom_pole[i]->vek, p_pom_pole[i]->jmeno);
  }
}

int sort_delsi(const void *p_a, const void *p_b)
{
  CLOVEK *p_1 = (CLOVEK *) p_a;
  CLOVEK *p_2 = (CLOVEK *) p_b;

  if (p_1->vek < p_2->vek)
    return -1;
  else if (p_1->vek == p_2->vek)
    return 0;
  else
    return +1;
}

int sort_kratsi(register const void *p_a, register const void *p_b)
{
  return (((CLOVEK *) p_a)->vek - ((CLOVEK *) p_b)->vek);
}

int sort_nejkratsi(register const void *p_a, register const void *p_b)
{
  return ((*((CLOVEK **) p_a))->vek - (*((CLOVEK **) p_b))->vek);
}

