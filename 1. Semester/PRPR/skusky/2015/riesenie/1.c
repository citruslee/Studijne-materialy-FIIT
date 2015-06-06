#include <stdio.h>

int main()
{
	int i = 5, j = 5, k = 5;

	if (i++ < ++k && ( i++ > ++j || j++ <= k++ ))
		i += j*k;

	printf("i = %d, j = %d, k = %d\n", i, j, k); // 56, 7, 7

	return 0;
}
