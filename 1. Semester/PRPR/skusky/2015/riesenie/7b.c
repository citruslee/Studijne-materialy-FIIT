// najdlhsia podpostupnost

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int n, i, j, dlzka, zaciatok;
	float *p, suma, akt_suma;

	printf("Zadajte pocet prvkov postupnosti: ");

	scanf("%d", &n);
	p = (float *) malloc(n * sizeof(float));

	for (i = 0; i < n; i++) {
		printf("%d-ty prvok: ", i);
		scanf("%f", &p[i]);
	}

	printf("Zadajte sumu: ");
	scanf("%f", &suma);

	dlzka = 0;
	
	for (i = 0; i < n; i++) {
		akt_suma = 0;
		j = i;

		while (j < n && akt_suma < suma) 
			akt_suma += p[j++];
			if (akt_suma == suma && j-i > dlzka) {
				dlzka = j-i;
				zaciatok = i;
		}
	}

	if (dlzka != 0) {
		for (i = zaciatok; i < zaciatok+dlzka; i++) 
			printf("%f, ", p[i]);
		puts("");
	}
	else
		printf("Podpostupnost neexistuje.\n");

	return 0;
}
