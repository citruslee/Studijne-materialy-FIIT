/*
 * Meno: 
 * Kruzok: 
 * Datum:  
 * Zadanie: zadanie06c
 * Kompilacia: cc pripravne_06c.c -o pripravne_06c
 *
 * Text zadania:
 * Napiste program, ktory v zadanom adresari adresar najde vsetky obycajne 
 * subory a ich prve riadky zapise do zadaneho suboru vsubor. 
 * Syntax:
 * zadanie2 [-h] adresar vsubor
 *  
 * Bonusove body mozete ziskat ak vas program bude prehladavat adresare 
 * rekurzivne do hlbky, alebo bude spracovavat lubovolny pocet adresarov 
 * prip. oboje.
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
void prehladaj(char *p_adresar, char *meno);
 
//------------------------------------------------------------------------
void main(int argc, char *argv[]) {
	int i,o;
	opterr = 0;
	while ((o = getopt(argc, argv, "h:")) != -1)
		switch (o) {
			case 'h':
				Help();
				exit(0);
			case '?':
			default:
				fprintf(stderr, "Error: '%c': nespravny prepinac\n", optopt);
				exit(1);
		}
	argc -= optind;
	argv += optind;

	if (argc == 0 )
//		printf("aktualny do default.txt\n");
		prehladaj(".", "out.txt");
	else if (argc == 1 )
//		printf("aktualny do %s\n", argv[0]);
		prehladaj(".", argv[0]);
	else {
		for (i=0; i < argc-1; i++) {
//		printf("adresa %s do %s\n", argv[i], argv[argc-1]);
			prehladaj(argv[i], argv[argc-1]);
		}
	}


}

//----------------------------------------------------------------- 
void prehladaj(char *p_adresar, char *meno){
	FILE *f1;
	char riadok[4096+1];
	struct dirent *entita;
	DIR *p_dir;
	struct stat st, st2;
	char newname[PATH_MAX];

	printf("func %s - %s\n",p_adresar, meno);

	if( (p_dir = opendir(p_adresar)) == NULL ) {
		fprintf(stderr,"Error '%s': Adresar sa nepodarilo otvorit !!\n", p_adresar);
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
			fprintf(stderr,"Error '%s': Chyba pri vykonavani lstat !!\n",newname);
			continue;
		}

		//klasika rekurzia na adresare...
		if(S_ISDIR(st.st_mode)) {
			prehladaj(newname, meno);
			continue;
		}

		//klasika rekurzia na adresare...
		if (S_ISREG(st.st_mode)) {
			fprintf(stdout, "Output: %s\n", newname);
			if ((f1 = fopen(newname,"r")) == NULL) {
				fprintf(stderr,"Error '%s': Nepodarilo sa otvorit na citanie!\n",newname);
				continue;
			}else{
				fgets(riadok, 4096, f1);
				printf("riadok = %s\n", riadok);				
				fclose(f1);
				if ((f1 = fopen(meno, "w")) == NULL) {
					fprintf(stderr,"Error '%s': Nepodarilo sa otvorit na zapis!\n",newname);
					continue;
				}else{
					fputs(strcat(riadok,"\n"), f1);
					printf("riadok saved = %s\n", riadok);				
					fclose(f1);
				
				}				
			}
		}

		
	}
	//toto testovanie mozno nemusi byt, ale u steiniho clovek niky nevie...
	if( (closedir(p_dir)) != 0 ) {
		fprintf(stderr,"Error: '%s': Nepodarilo sa zavriet adresar !!\n", p_adresar);
	}



}
//----------------------------------------------------------------- 
void Help() {
       printf("pripravne_06c.c (C) Michal Samiec\n\n");
       printf("Usage: pripravne_04c <arg1> <arg2> subor  \n\n");
       printf("   <arg>: adresar, v ktorom sa bude hladat, pokial sa nezada nic tak sa berie aktualny adreasar\n");
       printf("   subor: kam sa budu ukladat prve riadky z nacitavanych suborov\n\n");
}
