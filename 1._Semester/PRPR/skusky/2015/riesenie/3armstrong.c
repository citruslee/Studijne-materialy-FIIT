#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int armstrong(int x)
{
	char buffer[33];
	int i, y, d, value = 0;
	
	snprintf(buffer, 30, "%d", x);
	d = strlen(buffer);

	for (i = 0; i < d; ++i)
	{
		y = buffer[i] - 48;
		y *= y * y;
		value += y;
	}

	return value == x;
}

int main()
{
	int x = 371;

	if (armstrong(x))
		printf("%d je armstrongovo cislo\n", x);
	else
		printf("%d nie je armstrongovo cislo\n", x);

	return 0;
}
