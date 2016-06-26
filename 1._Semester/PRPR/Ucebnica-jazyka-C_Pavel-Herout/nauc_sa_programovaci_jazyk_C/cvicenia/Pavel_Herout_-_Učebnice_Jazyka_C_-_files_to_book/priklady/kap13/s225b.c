/*
 * s225b.c    v.2.0
 *
 * Pole retezcu
 * ============
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
  char *p_text[4];

  p_text[0] = "prvni";
  p_text[1] = "druhy";
  p_text[2] = (char *) malloc(6);
  strcpy(p_text[2], "treti");
  p_text[3] = "ctvrty";

  {  /* blok */
    char *p_pom = p_text[0];

    printf("Tisk prvniho retezce po znacich:\n");
    while (*p_pom != '\0')
      putchar(*p_pom++);
  }

  printf("\n\nTisk druheho retezce pomoci printf():\n");
  printf("%s\n", p_text[1]);

  printf("\nTisk tretiho retezce pomoci puts():\n");
  puts(p_text[2]);

  {  /* blok */
    char **p_pom = p_text;

    printf("\nChybny pokus o tisk prvniho pomoci puts():\n");
    puts(++*p_pom);
  }

  {  /* blok */
    char **p_pom = p_text;
    int i;

    /* oprava chybne nastaveneho prvniho retezce */
    (*p_pom)--;

    printf("\nTisk vsech retezcu pomoci puts():\n");
    for (i = 0;  i < 4;  i++)
      puts(*p_pom++);
  }
  return 0;
}

