#include <stdio.h>

int main(void)
{
  int i, *p_i;

  *p_i = 0;
  for (i = 1;  i <= 10;  i++) {
    *p_i += i;
    printf("i = %d  *p_i = %d\n", i, *p_i);
  }
  return 0; 
}

