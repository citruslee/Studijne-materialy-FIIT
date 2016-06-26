/*
 * hex-dec.c    v.2.0
 *
 * Konverze hexadecimalniho retezce na dekadicke cislo
 * ===================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#ifdef SELF
/* funkcni prototyp */
unsigned int shex2dec(char *shex);

int main(int argc, char *argv[])
{
  if (argc == 1) {
    fprintf(stderr, "Pouziti:  hex-dec hexa_cislo\n");
    exit(1);
  }
  printf("%s hexa = %u dek\n", argv[1], shex2dec(argv[1]));
  return 0;
}
#endif

unsigned int shex2dec(char *shex)
{
  unsigned char cislice;
  unsigned int vysledek = 0;

  for (; *shex != '\0'; shex++) {
    if (isxdigit(*shex) == 0) {
      fprintf(stderr, " '%c' neni hexa cislice\n", *shex);
      exit(1);
    }
    cislice = toupper(*shex);
    cislice -= (cislice <= '9')  ?  '0'  :  'A' - 10;
    vysledek = (vysledek << 4) + cislice;
  }
  return vysledek;
}

