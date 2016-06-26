// najkratsia postupnost
#include <stdio.h>
#include <stdlib.h>

int main() {
	int *p, n, i, j, dlzka, suma, akt_suma, zaciatok = -1;

	printf("Zadajte pocet prvkov postupnosti: ");
	scanf("%d", &n);
	p = (int *) malloc(n * sizeof(int));
	
	for(i = 0; i < n; i++) {
		printf("%d-ty prvok: ", i);
		scanf("%d", &p[i]);
	}

	printf("Zadajte sumu: ");
	scanf("%d", &suma);
	dlzka = n + 1;
	
	for (i = 0; i < n; i++) {
		akt_suma = 0;
		j = i;
		while (j < n && j-i+1 < dlzka && akt_suma < suma) {
			akt_suma += p[j];
			j++;
		}
		if (akt_suma == suma &&  (j-i) < dlzka) {
			dlzka = j-i;
			zaciatok = i;
		}
	}
	if (dlzka != n+1) {
		for (i = zaciatok; i < zaciatok+dlzka; i++) 
			printf("%d, ", p[i]);
		puts("");
	}
	else
		printf("Podpostupnost neexistuje.\n");
	
	return 0;
}
