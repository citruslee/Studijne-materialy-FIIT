#include <stdio.h>
#include <string.h>

void invert(unsigned *x1, unsigned *x2, int n, int i)
{
	unsigned mask = (~(~0<<n)<<i), y1, y2;

	y1 = *x1 & mask;
	y2 = *x2 & mask;
	*x1 = (*x1 & ~mask) | y2;
	*x2 = (*x2 & ~mask) | y1;
}

int main()
{
	unsigned a = 64, b = 32;
	invert(&a, &b, 1, 5);
	printf("a = %d, b = %d\n", a, b);

	return 0;
}
