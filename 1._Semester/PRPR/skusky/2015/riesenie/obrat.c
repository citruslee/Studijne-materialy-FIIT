#include <stdio.h>
#include <string.h>

int obrat(char *s, int zaciatok, int koniec)
{
	char tmp;

	if (koniec - zaciatok <= 0)
		return;
	
	tmp = s[zaciatok];
	s[zaciatok] = s[koniec];
	s[koniec] = tmp;

	obrat(s, zaciatok+1, koniec-1);
}

int main()
{
	char s[] = "gazda";

	obrat(s, 0, 4);

	printf("%s\n", s);

	return 0;
}
