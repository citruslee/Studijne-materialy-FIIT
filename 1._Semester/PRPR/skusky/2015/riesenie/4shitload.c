#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// konštanta
#define N 3

int **uprav(int m1[][N], int k)
{
	int i, j;

	// kedže potrebujem vratiť maticu von, musí byť dynamicky alokovaná v heape
	// ak by som ju alokoval v datovej oblasti, po ukončení vykonávania programu
	// by bola pamäť vrátená operačnému systému a on by ju poskytoval iným procesom

	// takže definujem smerník na maticu a hneď ho inicializujem na
	// pole N smerníkov, z ktorých každý bude ukazovať na n-tý riadok matice
	int **m2 = (int **) malloc(N * sizeof(int *));

	// teraz potrebujeme alokovať miesto pre samotné bunky matice (matica je kvázi tabuľka)
	// to sa dá dosiahnuť napr. dvoma spôsobmi buď
	// a) alokujem maticu po riadkoch: N polí o N prvkov čím dostanem N kusov pamäte, alebo
	// b) naraz alokujem miesto pre všetky bunky matice, čím docielým, že dostanem celý kus pamäte
	// ja rád používam druhý spôsob
	int *space = (int *) calloc(N*N, sizeof(int));

	// keď už mám pamäť pre maticu aj ukazovatele na riadky,
	// je načase nasmerovať ich na našu pamäť. Yay!
	for (i = 0; i < N; ++i)
		// m2 je pole pointerov
		// m2[i] je pointer na i-tý riadok matice
		// space je pointer na blok pamäte reprezentujúci našu maticu
		// kedže space predstavuje adresu, pomocou pointrovej aritmetiky smerujeme pointre
		// na jednotlivé riadky offsetom dĺžky riadka, 0, N, 2N, 3N ... 
		m2[i] = space + (i * N);

	// v tomto bode už sú smerniky žvonzíky nasmerované a môžeme cez pointer na pointer na int (m2)
	// 2x dereferencovať ako so staticky alokovaným poľom: m2[i][j]...
	// čo aj medzi bratmi kompilermi sa prekladá na *(*(m2+i)+j)
	// no a keďže sme maticu alokovali ako nulovú, stačí nam len prvky pod diagonálou 
	// pôvodnej matice vynásobiť konštantou a uložiť do novej matice
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			if (i > j)
				m2[i][j] = k * m1[i][j]; 

	// Lord of Pointers: Return of the Matrix
	return m2;
}

// na testovanie
void vypis(int **m2)
{
	int i, j;
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j)
			printf("%3d", m2[i][j]);
		puts("");
	}
}

int main()
{
	int m1[][N] = {
		{1, 1, 1},
		{2, 2, 2},
		{3, 3, 3}
	};

	// Trubky: m2 ma 2 hviezdičky, tak aj funkcia uprav musí vracať 2 hviezdičky :D
	int **m2 = uprav(m1, 2);

	// a už sme dobrí
	vypis(m2);

	return 0;
}
