#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* funkcia(char* str, int s, int k)
{
	int d2 = k - s + 1;
	char* p = malloc(d2+1); 

	strncpy(p, str+s, d2);
	p[d2] = '\0';

	return p;
}

int main()
{

	char str[] = "mama ma emu";

	// podretazec str od s (start) po k (koniec)
	printf("%s\n", funkcia(str, 0, 4));

	return 0;
}
