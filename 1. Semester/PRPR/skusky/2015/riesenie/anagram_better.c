#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void bubble_sort(char *s, int n)
{
	int i, j, min;
	char tmp;

	for (i = 0; i < n; ++i)
	{
		min = i;
		for (j = i; j < n; ++j)
		{
			if (s[j] < s[min])
				min = j;
		}
		tmp = s[min];
		s[min] = s[i];
		s[i] = tmp;
	}
}

int anagram(char *a1, char *a2)
{
	char *c1, *c2;
	int d1, d2, is_anagram;

	d1 = strlen(a1);
	d2 = strlen(a2);

	if (d1 != d2)
		return 0;

	c1 = malloc(d1+1);
	c2 = malloc(d1+1);

	strcpy(c1, a1);
	strcpy(c2, a2);

	bubble_sort(c1, d1);
	bubble_sort(c2, d1);

	is_anagram = strcmp(c1, c2) == 0;

	printf("c1: %s\n", c1);
	printf("c2: %s\n", c2);
	
	free(c1);
	free(c2);

	return is_anagram;
}

int main(int argc, char const *argv[])
{
	char s[] = "mars";
	char s2[] = "sram";

	printf("%s a %s %s anagramy\n", s, s2, anagram(s, s2) == 1 ? "su" : "nie su");

	return 0;
}
