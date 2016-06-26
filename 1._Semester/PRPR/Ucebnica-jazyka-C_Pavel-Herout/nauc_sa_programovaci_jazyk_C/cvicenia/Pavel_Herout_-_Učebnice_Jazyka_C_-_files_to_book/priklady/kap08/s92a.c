/*
 * s92a.c    v.2.0
 *
 * Pouziti symbolicke konstanty v programu
 * =======================================
 */

#include <stdio.h>

#define DVE_PI  (2 * 3.14)

int main()
{
  double r;

  printf("Zadej polomer: ");
  scanf("%lf", &r);
  printf("Obvod kruhu s polomerem %f je %f\n",
          r, r * DVE_PI);
  return 0;
}

