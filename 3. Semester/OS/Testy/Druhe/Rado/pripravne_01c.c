/*
 * Meno: Rado Orsula
 * Kruzok: op1
 * Datum: 13.12.2005 
 * Zadanie: zadanie01c
 * Kompilacia: cc pripravne_01c.c -o pripravne_01c
 *
 * Text zadania:
 * Napiste program, ktory v zadanom adresari, uvedenom ako argument, najde
 * vsetky vykonatelne C-shell-ovske skripty (prvy riadok skriptu obsahuje
 * napr. "#!/bin/csh", resp. regularny vyraz "#!.*csh").
 * Na identifikaciu skriptu MUSITE pouzit program grep, ktoreho vystup budete
 * citat cez ruru.
 *  
 * Syntax:
 * zadanie2 [-h] adresar 
 *  
 * Format vystupu (na standardny vystup):
 * Output: '<skript>'
 *  
 * Bonusove body mozete ziskat ak vas program bude vediet prehladavat lubovolny
 * pocet zadanych adresarov (ak nebude adresar uvedeny, prehladava sa aktualny
 * pracovny adresar), pripadne ak bude adresare prehladavat rekurzivne do hlbky.
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
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <errno.h>

void Help();
void SearchDir(char *adr);
int Testuj (char *meno);


 
int main(int argc, char *argv[]) {
	int o;
 
	opterr = 0;
	while ((o = getopt(argc, argv, "h")) != -1)
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

  if (argc == 0) SearchDir(".");
   else {
   	while ( argc > 0 )
   	 	{ 
   	 	SearchDir(argv[0]);
   	 	argv++;
   	 	argc--;
   	 	}
        }
       
}



void SearchDir (char *adr)
{
  int test;
  DIR *dp;
  struct dirent *dir;
  char newname[200];
  struct stat buf;
  
  if ((dp=opendir(adr))==NULL) {
  	fprintf(stderr,"Error: 'Chyba pri citani adresara %s %d '\n",adr,errno);
	return;
   	}
  
  while((dir=readdir(dp)) != NULL) {
  	if ( dir ->d_ino == 0) continue;
  	if ( (strcmp (dir -> d_name, ".") == 0) || (strcmp (dir-> d_name, "..") == 0))
  	continue;
  	
  	sprintf(newname,"%s/%s",adr,dir->d_name);
  	stat(newname,&buf);
  	if (((buf.st_mode & S_IRWXU) & S_IRUSR) == 0) {
  	     fprintf(stderr,"Error: nemozem citat %s\n",dir->d_name);
  	     continue;
  	}
  	
  	if ( S_ISDIR(buf.st_mode)) {
  		SearchDir(newname);
  		continue;
  		}
  		
  	if ( !S_ISREG(buf.st_mode)) continue;
  	
  	test = Testuj(newname);
  	
  	switch (test) {
  		case -1:
  			fprintf(stderr,"Error: nemozem otestovat %s\n",newname);
  			continue;
  		case 0: continue;
  		default: fprintf(stdout,"Output: '%s'\n",newname);
  			}
  	}
}  
  
int Testuj(char *meno)
 { 
 FILE *f;
 int fd[2];
 int out[2];
 char riadok[21];
 char poc[21];
 int pocet;
 
 if ((f=fopen(meno,"r")) == NULL) {
 	fprintf(stderr,"Error: %s: nemozem otvorit pre citanie \n",meno);
 	return -1;
 	}
if ( pipe(fd) < 0 ) {
	fprintf(stderr,"Error: 'Nemozem vytvorit PIPE(fd)'\n");
	exit(1);
	}
	
if ( pipe(out) < 0 ) {
	fprintf(stderr,"Error: 'Nemozem vytvorit PIPE(out)'\n");
	exit(1);
	}
	
  switch ( fork() ) {
        case -1:
  		fprintf (stderr,"Error: chyba pri fork 1\n");
  		exit (1);
  		break;
  	case  0:
  		close (fd[0]);
  		close (1);
  		dup (fd[1]);
  		close (fd[1]);
  		fgets(riadok,20,f);
  		printf("%s",riadok);
  		exit(0);
  		break;
  	default:
    
		close (fd[1]);
		wait(0);
  
		switch( fork() ) {
			case -1:
				fprintf(stderr,"Error: chyba pri fork 2\n");
				exit(1);
				break;
		case 0:
			close (fd[1]);
			close (out[0]);
			close (0);
			dup (fd[0]);
			close (fd[0]);
			close (1); 
			dup (out[1]); /* este jeden */
			execlp("grep","grep","-c","#!.*csh",NULL);
				fprintf(stderr,"Error: nemozem vykonat grep\n");
				exit(1);
				break;
		default:
			close (out[1]);
			read(out[0],poc,20);
			pocet = atoi(poc);
		}
  }  
wait(0);
return pocet;
  }
  
void Help() {
	printf("Test2 (C)\n");
	printf("Test2 [-h] adresar\n");
	printf("          -h: help\n");
	printf("     adresar: prehladavany adresar \n\n\n");
	
}
