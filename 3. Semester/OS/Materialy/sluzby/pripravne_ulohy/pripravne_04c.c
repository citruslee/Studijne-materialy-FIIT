/*
 * Meno: 
 * Kruzok: 
 * Datum:  
 * Zadanie: zadanie04c
 * Kompilacia: cc pripravne_04c.c -o pripravne_04c
 *
 * Text zadania:
 * Napiste program, ktory v zadanom adresari, uvedenom ako argument, a jeho
 * podadresaroch, najde vsetky symbolicke linky.
 * Ak bude program spusteny s prepinacom -e, vyhlada len linky s existujucim 
 * cielovym suborom; s prepinacom -n len linky s neexistujucim cielovym suborom.
 * Program NESMIE pouzivat na prehladavanie adresara externy program (musi
 * prehladavat adresar rekurzivne).
 *  
 * Syntax:
 * zadanie2 [-h] [-e] [-n] adresar
 *  
 * Format vystupu (na standardny vystup):
 * Output: 'najdena linka'
 *  
 * Bonusove body mozete ziskat ak vas program bude vediet prehladavat lubovolny
 * pocet zadanych adresarov (ak nebude adresar uvedeny, prehladava sa aktualny
 * pracovny adresar).
 *
 * Rieste aj cast zadania oznacenu ako bonusovu.
 *
 * Program musi osetrovat pocet a spravnost argumentov. Program musi mat help,
 * ktory sa vypise pri zadani argumentu -h a ma tvar:
 * Meno programu (C) meno autora
 *  
 * Usage: <meno_programu> <arg1> <arg2> ...
 *    <arg1>: xxxxxx
 *    <arg2>: yyyyy
 *  
 * Korektny vystup programu musi ist na standardny vystup (stdout).
 * Chybovy vystup programu musi ist na chybovy vystup (stderr).
 * Chybovy vystup musi mat tvar:
 * Error: 'adresar, subor, program,... pri ktorom nastala chyba': popis chyby ...
 * Ak program pouziva nejake pomocne vypisy, musia ist na chybovy vystup a 
 * musia mat tvar:
 * Debug: vypis ...
 *  
 * Program sa musi dat skompilovat !!!
 * Prikaz pre kompilaciu je uvedeny vyssie, v pripade potreby ho modifikujte !!!
 *
 * Poznamky: (sem vlozte pripadne poznamky k vypracovanemu zadaniu)
 * 
 * Riesenie:
 */
 
#include <stdio.h>
#include <unistd.h>
 
void Help();
 
void main(int argc, char *argv[]) {
	int o;
 
	opterr = 0;
	while ((o = getopt(argc, argv, "hp:")) != -1)
		switch (o) {
			case 'h':
				Help();
				exit(0);
/*	prepinac s jednym parametrom
			case 'p':
				printf("Output: '%s': parameter prepinaca -p\n", optarg);
				exit(0);
*/
			case '?':
			default:
				fprintf(stderr, "Error: '%c': nespravny prepinac\n", optopt);
				exit(1);
		}
	argc -= optind;
	argv += optind;
}
 
void Help() {
/* Sem treba dopisat help */
	printf("Tu by mal byt help\n");
}
