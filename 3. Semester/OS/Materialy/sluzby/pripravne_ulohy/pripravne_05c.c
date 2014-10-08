/*
 * Meno: 
 * Kruzok: 
 * Datum:  
 * Zadanie: zadanie05c
 * Kompilacia: cc pripravne_05c.c -o pripravne_05c
 *
 * Text zadania:
 * Napiste program, ktory spusti tri zadane prikazy, pricom standardny
 * vystup prveho bude presmerovany na standardny vstup druheho a standardny 
 * vystup druheho na vstup tretieho. Prikazy su uvedene ako argumenty
 * na prikazovom riadku. Tieto tri prikazy nemaju svoje argumenty.
 * Syntax:
 * zadanie2 [-h] prik1 prik2 prik3
 * Priklad pouzitia:
 * zadanie2 ls cat wc
 *  
 * Bonusove body mozete ziskat ak vas program bude spracovavat prikazy 
 * aj s ich argumentami (prikazy oddelene bodkociarkami), alebo bude 
 * spracovavat lubovolny pocet prikazov, prip. oboje.
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
