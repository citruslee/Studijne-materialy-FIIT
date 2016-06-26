/*
 * Meno: 
 * Kruzok: 
 * Datum:  
 * Zadanie: zadanie02c
 * Kompilacia: cc pripravne_02c.c -o pripravne_02c
 *
 * Text zadania:
 * Napiste program, ktory zisti, ci je prihlaseny zadany pouzivatel uziv 
 * a v pripade, ze je prihlaseny, prida do suboru vyst zaznam o vsetkych
 * procesoch, ktore ma pouzivatel spustene. Na zistenie spustenych procesov 
 * pouzite (povinne) vystup prikazu 'ps -U <uziv>' a tento citajte cez ruru.
 *    
 * Syntax: 
 * zadanie2 [-h] uziv vyst
 *    
 * Format zaznamu v subore vyst:
 * Output: '<pouzivatel> <pid> <meno procesu s jeho argumentami>'
 *      
 * Bonusove body mozete ziskat ak vas program bude zaznamenavat do suboru vyst
 * aj datum a cas, kedy bol zaznam o procesoch urobeny.
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
#include <sys/syslimits.h>
#include <time.h>
#include <utmp.h>
#include <sys/types.h>
#include <fcntl.h>

 
char *logfile[255];
void Help();
int JePrihlaseny(char *meno);  

void main(int argc, char *argv[]) {
	int o;
	int fd[2];
	time_t cas; 
	char c;
	FILE *f;  
	opterr = 0;
	while ((o = getopt(argc, argv, "h")) != -1)
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
	
	if (JePrihlaseny(argv[0]) != 1) exit(1);
	if (argc != 2)
		fprintf(stderr, "Error: 'nespravny pocet argumentov \n'", argc);

	if ( (f=fopen(argv[1],"a")) == NULL) {
		fprintf(stderr,"Error: 'nemozem otvorit subor %s'\n",argv[1]);
		exit(1);
	} 
	
	if ( pipe(fd) < 0 ) {
		fprintf(stderr,"Error: 'chyba pri PIPE'\n");
		exit(1);
	}


	switch(fork()){
		case -1:
			fprintf(stderr, "Error: 'zlyhal fork'");
//			fclose(fd[0]);
//			fclose(fd[1]);
			exit(1);
			break;
		case 0:
			close(fd[0]);
			close(1);
			dup(fd[1]);
			close(fd[1]);
			execlp("ps","ps","-h","-U",argv[0],"-o","user,pid,command",NULL);
			fprintf(stderr,"Error: 'chyba pri exec'\n");
			exit(1);
			break; 
		default:
			close(fd[1]);
			cas = time(NULL);
			fprintf(f,"\n%s", ctime(&cas));

			while (1) {
		     		if (read(fd[0], &c, 1) == 0) break;
				fprintf(f, "\nOutput: '%c",c);
				while(read(fd[0], &c, 1) != 0) {
					if ( c != '\n') fprintf (f,"%c",c);
		       		else break;
       			}
				fprintf(f,"'");
			}
			fclose(f);
			close(fd[0]); 
			break;
	}
}
//---------------------------------
int JePrihlaseny(char *meno){
	FILE *f;
	int f1;
	struct utmp logstruct;

	if ((f1 = open(_PATH_UTMP, O_RDONLY)) == NULL){
		fprintf(stderr, "Error: 'neda sa otvorit subor %s\n'", _PATH_UTMP);
		return -1;
	}
	
	while (read(f1, &logstruct, sizeof(logstruct)) !=0)
		if (strcmp(meno, logstruct.ut_name) == 0) return 1; 
	fprintf(stdout, "OUTPUT: 'Uzivatel '%s' nieje prihlaseny %s\n'", meno);
	close(f1);
	return 0;
	
}

//---------------------------------
void Help() {
       printf("Pripravne_02c.c (C) Michal Samiec\n");
       printf("Usage: <meno_programu> uziv\n");
       printf("   <uziv>: meno uzivatela o ktorom ma byt info o procesoch\n");
       printf("  <subor>: subor do ktoreho pojde vystup (default logfile)\n");
}
 
