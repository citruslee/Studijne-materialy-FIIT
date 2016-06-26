/*
 * s412.c    v.2.0
 *
 * Nove formatove specifikace
 * ==========================
 */

#include <stdio.h>
#include <stddef.h>

int main(int argc, char **argv)
{
  signed char sc = -1;
  unsigned char usc = 255;
  signed long long int slli = -123456789012345LL;
  unsigned long long int uslli = 123456789012345LL;
  size_t st = 789;
  ptrdiff_t ptr = argv[1] - argv[0];
/*  intmax_t imax = -1234567890;
  uintmax_t uimax = 1234567890;
*/

  printf("%%hhd = %hhd\n", sc);
  printf("%%hhu = %hhu\n", usc);
  printf("%%LLd = %LLd\n", slli);
  printf("%%LLu = %LLu\n", uslli);
  printf("%%z   = %z\n", st);
  printf("%%t   = %t\n", ptr);
/*  printf("%%jd  = %jd\n", imax);
  printf("%%ju  = %ju\n", uimax);
*/
  return 0;
}

