/*
 * s423.c    v.2.0
 *
 * Retezcove operace s vicebajtovymi retezci
 * =========================================
 */
#include <stdio.h>
#include <wchar.h>

int main(void)
{
  wchar_t wstr1[10] = L"Ahoj";
  wchar_t wstr2[10];
  int delka;

  wcscpy(wstr2, wstr1);
  delka = wcslen(wstr2);
  printf("%d\n", delka);

  return 0;
}

