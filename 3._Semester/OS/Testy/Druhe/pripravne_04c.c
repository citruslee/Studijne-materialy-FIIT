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
 
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/syslimits.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void Help();
void prehladaj(char *p_adresar, int menu);
 
//------------------------------------------------------------------------
void main(int argc, char *argv[]) {
	int o;
	int o2;
 
	opterr = 0;
	while ((o = getopt(argc, argv, "hen")) != -1){
	o2 = o;
		switch (o) {
			case 'h':
				Help();
				exit(0);
			case 'e':
				if (argc == 2) prehladaj(".", o);
				else prehladaj(argv[2], o);
				break;
			case 'n':
				if (argc == 2) prehladaj(".", o);
				else prehladaj(argv[2], o);
				break;
			case '?':
			default:
				fprintf(stderr, "Error: '%c': nespravny prepinac\n", optopt);
				exit(1);
		}
	}
	argc -= 3;
	argv += 3;
	if (argc == -2)
		prehladaj(".", argc);
	if (argc == -1 && optind == 1)
		prehladaj(argv[-2], -2);
	if (argc > 0 )
		while(argc > 0) {
			prehladaj(argv[0], o2);
			argc--;
			argv++;
		}


}

//----------------------------------------------------------------- 
void prehladaj(char *p_adresar, int menu){
	struct dirent *entita;
	DIR *p_dir;
	struct stat st, st2;
	char newname[PATH_MAX];

//		printf("\t*** *** *** FUNC\n");


	if( (p_dir = opendir(p_adresar)) == NULL ) {
//		fprintf(stderr,"Error '%s': Adresar sa nepodarilo otvorit !!\n", p_adresar);
		return;
	}
	
	//klasika...
	while(entita = readdir(p_dir)) {
	
		if( (strcmp(entita->d_name,".") == 0) || (strcmp(entita->d_name,"..") == 0) )
			continue;

		//klasika...
		strcpy(newname,p_adresar);

		if(p_adresar[strlen(p_adresar)-1] != '/')
			strcat(newname,"/");

		strcat(newname,entita->d_name);

		if( (lstat(newname,&st)) != 0) {
//			fprintf(stderr,"Error '%s': Chyba pri vykonavani lstat !!\n",newname);
			continue;
		}

		//klasika rekurzia na adresare...
		if(S_ISDIR(st.st_mode)) {
			prehladaj(newname, menu);
			continue;
		}

		//klasika rekurzia na subory...
		if(S_ISLNK(st.st_mode)) {
			if (menu == -2)
				fprintf(stdout, "Output: '%s'\n", newname);
			else if ((stat(newname,&st2) != 0) && (menu=='n')) {
				fprintf(stdout, "Output: '%s'\n", newname);
			}else if ((stat(newname,&st2)==0) && (menu == 'e')){
				fprintf(stdout, "Output: '%s'\n", newname);
			}
		
			continue;
		}

		if(!(S_ISREG(st.st_mode))) {
			continue;
		}

	}
	//toto testovanie mozno nemusi byt, ale u steiniho clovek niky nevie...
	if( (closedir(p_dir)) != 0 ) {
		fprintf(stderr,"Error: '%s': Nepodarilo sa zavriet adresar !!\n", p_adresar);
	}



}
//----------------------------------------------------------------- 
void Help() {
/* Sem treba dopisat help */
       printf("pripravne_04c.c (C) Michal Samiec\n\n");
       printf("Usage: pripravne_04c -h -e -n <arg1> <arg2> ...\n\n");
       printf("   -h: vypise help\n");
       printf("   -e: vypise symbolicke lilnky, pri ktorych existuje subor na ktor7 sa linkuju\n");
       printf("   -n: vypise symbolicke lilnky, pri ktorych neexistuje subor na ktor7 sa linkuju\n");
       printf("   <arg1>: adresar, v ktorom sa bude hladat, pokial sa nezada nic tak sa berie aktualny adreasar\n");
//       printf("   <argx>: arguemnty <arg3>\n\n");
}
