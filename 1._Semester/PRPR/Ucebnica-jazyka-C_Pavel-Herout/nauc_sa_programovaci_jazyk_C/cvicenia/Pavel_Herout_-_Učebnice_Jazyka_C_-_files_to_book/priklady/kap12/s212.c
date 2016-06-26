/*
 * s212.c    v.2.0
 *
 * Priklady ruznych formatu tisku
 * ==============================
 */

#include <stdio.h>
#include <string.h>

#define I 555
#define R 5.5

int main(void)
{
  int i,j,k,l;
  char buf[7];
  char *priznak = buf;
  char format[20];

  printf("priznak|  6d   |  6o   |  8x     |  10.2e    |   10.2f   |\n");
  printf("=======|=======|=======|=========|===========|===========|\n");
  strcpy(priznak, "%");
  for (i = 0; i < 2; i++) {
    for (j = 0; j < 2; j++) {
      for (k = 0; k < 2; k++) {
        for (l = 0; l < 2; l++) {
          if (i == 0)
            strcat(priznak, "-");
          if (j == 0)
            strcat(priznak, "+");
          if (k == 0)
            strcat(priznak, "#");
          if (l == 0)
            strcat(priznak, "0");
          printf("%6s |",priznak);
          strcpy(format, priznak);
          strcat(format, "6d |");
          printf(format, I);
          strcpy(format, "");
          strcpy(format, priznak);
          strcat(format, "6o |");
          printf(format, I);
          strcpy(format, "");
          strcpy(format, priznak);
          strcat(format, "8x |");
          printf(format, I);
          strcpy(format, "");
          strcpy(format, priznak);
          strcat(format, "10.2e |");
          printf(format, R);
          strcpy(format, priznak);
          strcat(format, "10.2f |");
          printf(format, R);
          printf("  \n");
          strcpy(priznak, "%");
        }
      }
    }
  }
  return 0;
}

