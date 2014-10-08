/*
 * Meno: Marek Zelem & Ing. Branislav Steinmuller
 * Kruzok: odborne praktikum - OS
 * Datum:  
 * Zadanie: zadanie32c
 * Kompilacia: cc zelem_32c.c -o zelem_32c
 *
 * Text zadania:
 * Napiste program, ktory ma ako argumenty 2 subory vstup1 a vstup2 a na 
 * standardny vystup zapise postupne prve, druhe, ... riadky z oboch vstupnych 
 * suborov. Pritom vsetky pismena zo suboru vstup1 skonvertuje na velke
 * a vsetky pismena zo suboru vstup2 skonvertuje na male. Na konverziu pouzite
 * (povinne) program tr (napr. tr '[:lower:]' '[:upper:]').
 *   
 * Syntax:
 * zadanie2 [-h] vstup1 vstup2
 *   
 * Bonusove body mozete ziskat ak program bude spracovavat lubovolny pocet dvojic 
 * vstupnych suborov (zadana musi byt aspon jedna dvojica).
 *
 * Program musi osetrovat pocet a spravnost argumentov. Program musi mat help,
 * ktory sa vypise pri zadani argumentu -h a ma tvar:
 * Meno programu (C) meno autora
 * Usage: <meno_programu> <arg1> <arg2> ...
 *    <arg1>: xxxxxx
 *    <arg2>: yyyyy
 * Korektny vystup programu musi ist na standardny vystup (stdout).
 * Chybovy vystup programu musi ist na chybovy vystup (stderr).
 * Chybovy vystup musi mat tvar:
 * Error: 'adresar, subor, program,... pri ktorom nastala chyba': popis chyby ...
 * Ak program pouziva nejake pomocne vypisy, musia ist na chybovy vystup a 
 * musia mat tvar:
 * Debug: vypis ...
 * Nedodrzanie formatu vystupov bude mat za nasledok stratu 5 bodov !!!
 * Program sa musi dat skompilovat !!! V opacnom pripade bude ohodnoteny 0 bodmi.
 * Prikaz pre kompilaciu je uvedeny vyssie, v pripade potreby ho modifikujte !!!
 * ZMENA oproti pravidlam uvedenym v subore /ped/OS/Pri.pocitaci:
 * zadanie NEMUSI obsahovat subor 'Makefile' (ale moze).
 *
 * Poznamky: (sem vlozte pripadne poznamky k vypracovanemu zadaniu)
 * 
 * Riesenie:
 */
 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

void Help();

void main(int argc, char *argv[]) {
	int f1,f2;
	int fd[2];
	FILE *lw2up,*up2lw;
	int end;
	char buf[1024];
 	
	if( 1<argc && argv[1][0]=='-' && argv[1][1]=='h' )
	{	Help();
		exit(0);
	}
	argv++; argc--;
	/* test na minimalny a parny pocet argumentov */
	if( argc<2 || (argc & 1) )
	{	fprintf(stderr,"Error: Nespravny pocet argumentov\n");
		exit(0);
	}

	/* cyklus cez vsetky dvojice suborov */
	while( argc>1 )
	{	if( (f1=open(argv[0],O_RDONLY))== -1 )
		{	fprintf(stderr,"Error: '%s': Nemozem otvorit subor\n",
				argv[0]);
			exit(0);
		}
		if( (f2=open(argv[1],O_RDONLY))== -1 )
		{	fprintf(stderr,"Error: '%s': Nemozem otvorit subor\n",
				argv[1]);
			exit(0);
		}

		/* spustenie progamov tr */
	        pipe(fd);
        	switch( fork() )
	        {       case 0: close(0);
        	                dup(f1); close(f1);
				close(1); dup(fd[1]);
				close(fd[1]); close(fd[0]);
        	                execlp("tr","tr","[:lower:]","[:upper:]",NULL);
                	case -1:
				fprintf(stderr,"Error: 'tr': Nemozem spusit\n");
        	                exit(1);
                	default:
				close(f1);
                        	close(fd[1]);
	        }
        	if( (lw2up=fdopen(fd[0], "r"))== NULL )
		{	fprintf(stderr,"Error: 'lw2up': Nemozem urobit fdopen\n");
			exit(0);
		}
	        pipe(fd);
        	switch( fork() )
	        {       case 0: close(0);
        	                dup(f2); close(f2);
				close(1); dup(fd[1]);
				close(fd[1]); close(fd[0]);
        	                execlp("tr","tr","[:upper:]","[:lower:]",NULL);
                	case -1:
				fprintf(stderr,"Error: 'tr': Nemozem spusit\n");
	                        exit(1);
        	        default:
        	        	close(f2);
                	        close(fd[1]);
	        }
        	if( (up2lw=fdopen(fd[0], "r"))== NULL )
		{	fprintf(stderr,"Error: 'up2lw': Nemozem urobit fdopen\n");
			exit(0);
		}

		end=0;
		/* cyklus cez vsetky riadky */
		while( !end )
		{	end=1;	/* je koniec */
			if( fgets(buf,sizeof(buf),lw2up) )
			{	end=0; /* nieje koniec */
				write(1,buf,strlen(buf));
			}
			if( fgets(buf,sizeof(buf),up2lw) )
			{	end=0; /* nieje koniec */
				write(1,buf,strlen(buf));
			}
		}
		fclose(lw2up); fclose(up2lw);
		/* posun argumenty */
		argv+=2; argc-=2;
	}
	wait(NULL);
	wait(NULL);
}
 
void Help() {
	printf(	"Zadanie 32c (c) Marek Zelem\n"
		"Usage: zadanie_32c [-h] <subor1> <subor2> [<subor1> <subor2>] ...\n"
		"	-h: help\n"
		"	<subor1>: meno prveho suboru\n"
		"	<subor2>: meno druheho suboru\n");
}
