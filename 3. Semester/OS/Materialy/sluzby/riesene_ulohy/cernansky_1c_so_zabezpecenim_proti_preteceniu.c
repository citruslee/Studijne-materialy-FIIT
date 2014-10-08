/*
 * Meno: Michal Cernansky
 * Kruzok: odborne praktikum - OS
 * Datum: 28.10.1999  
 * Zadanie: zadanie1c
 * Kompilacia: cc cernans_1c.c -o searchpattern
 *
 * Text zadania:
 * Napiste program, ktory v zadanom adresari, uvedenom ako argument, najde
 * vsetky obycajne subory a v nich zisti pocet riadkov, na ktorych sa nachadza
 * zadany retazec. Na najdenie tychto riadkov pouzite (povinne) program grep 
 * s pripadnymi prepinacmi a jeho vystup citajte cez ruru.
 * Syntax:
 * zadanie2 [-h] adresar retazec
 * Format vystupu (na standardny vystup):
 * Output: '<subor>: <pocet najdenych riadkov>'
 * Bonusove body mozete ziskat ak vas program bude vediet prehladavat lubovolny
 * pocet zadanych adresarov (ak nebude adresar uvedeny, prehladava sa aktualny
 * pracovny adresar), pripadne ak bude adresare prehladavat rekurzivne do hlbky.
 * ~
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
 * zistovat, ci mozem citat ( read access )
 * 
 * Riesenie:
 */
 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/syslimits.h>

void Help();					// zobrazi help
void SearchDir(char *dirname,char *pattern);	// prehlaadava zadany adresar
int PrintCount(char *filename,char *pattern);	// zisti pocet suborov
 
void main(int argc, char *argv[]) 
{
	int i;
	int o;
 	
	opterr = 0;
	while ((o = getopt(argc, argv, "h")) != -1)	// prehladavanie vst. arg.
		switch (o) 
		{
			case 'h':			// argument bol -h
				Help();
				exit(0);
			case '?':
			default:
				fprintf(stderr, "Error: '%c': nespravny prepinac\n", optopt);
				exit(1);
		}
	argc -= optind;
	argv += optind;
	
	if(!argc)	// aspon retazec mal byt zadany
	{
		fprintf(stderr,"Error: chyba retazec\n");
		exit(1);
	}
	if(argc==1)	// iba retazec zadany, hladame v adresari .
		SearchDir(".",argv[0]);
	else		// zadane aj mena adresarov, tak cez vsetky
		for(i=0;i<argc-1;i++)
			SearchDir(argv[i],argv[argc-1]);
}
 
// vypisanie helpu
void Help() 
{
	printf("\n");
	printf("searchpattern  (C) Michal Cernansky\n");
	printf("Usage : searchpattern [-h] [directory1 [dirctory2 [..]]] pattern\n");
	printf("  -h         : vypise help\n");
	printf("  directoryX : nazvy adresarov kde hladat retazec\n");
	printf("               ak nezadane,prehladava aktualny adresar\n");
	printf("  pattern    : hladany retazec\n");
	printf("\n");
}

void SearchDir(char *dirname,char *pattern)	// prehladavanie adresara
{
	DIR *dp;
	struct dirent *dir;
	char path[PATH_MAX];
	int count;
	struct stat filestat;
			
	if((dp = opendir(dirname))==NULL)	// pokus o otvorenie adresara
	{
		fprintf(stderr,"Error: '%s': chyba pri otvarani adresara\n",dirname);
		return;
	}

	while((dir=readdir(dp)) != NULL)	// citame adresar
	{
// toto nie je potrebne
//		if(dir->d_ino == 0)		// nic tak ideme dalej
//			continue;
		strncpy(path,dirname,sizeof(path)); // poskladame meno suboru
		path[sizeof(path)-1] = '\0';
		
		if(dirname[strlen(dirname)-1] != '/') // nie je tam slash
			strncat(path,"/",sizeof(path)-1); // tak ho pridame
		strncat(path,dir->d_name,sizeof(path)-1);
		if(lstat(path,&filestat) != 0) {// zistime typ suboru
			fprintf(stderr,"Error: '%s': chyba pri lstat\n",dirname);
			continue;
		}
		
						// adresare . aa ..
		if((strcmp(dir->d_name,".")==0)||(strcmp(dir->d_name,"..")==0))
			continue;
			
						// nefunguje
//		if(!(S_IRUSR  & (filestat.st_mode & S_IFMT)))
						// toto by uz malo, ale
						// testuje len prava vlastnika
						// suboru
		if(!(S_IRUSR  & (filestat.st_mode & S_IRWXU)))
		{
			fprintf(stderr,"Error: '%s': nemozem citat subor\n",dir->d_name);
			continue;
		}
	
			
		if(S_ISDIR(filestat.st_mode))	// adresar, vnorime sa
		{
			SearchDir(path,pattern);
			continue;
		}
		
		if(!S_ISREG(filestat.st_mode))	// reguler. subor
			continue;	
		
		count = PrintCount(path,pattern); // zistime pocet
		if(count >= 0)		
			printf("%s > %d\n",path,count);
		else
			fprintf(stderr,"Error: '%s': nemozem zistit pocet vyskytov\n",path);
		
	}

	closedir(dp);
}

// velkost riadku na nacitane cislo od grepu ako define
#define NUMBER_SIZE 20
int PrintCount(char *filename,char *pattern)	// zistenie poctu vyskytov retazca
{
	int pipedes[2];				// deskriptory pre datovod
	int count;				// zisteny pocet vyskytov
	char number[NUMBER_SIZE+1];		// riadok s cislom od grepu
	
	count = -1;	
	if(pipe(pipedes))			// vytvorime datovod
	{
		fprintf(stderr,"Error: volanie pipe zlyhalo\n");
		exit(1);
	}
		
	switch(fork())				// vvytvorime dcersky proces
	{
		case -1 :			// zlyhanie forku
			fprintf(stderr,"Error: chyba pri fork\n");
			return -2;
		case 0 :			// dcersky proces
			
			close(pipedes[0]); // zatvorenie vystupu z datovodu
			close(1);	   // zatvorenie std. vystupu
			dup(pipedes[1]);   // dupl. vstupu datovodu na desc. 1
			close(pipedes[1]); // zatvorenie vstupu datovodu
			
						// spudtenie grep-u
			fclose(stderr);
			execlp("grep","grep","-c",pattern,filename,0);
			fprintf(stderr,"Error: spustanie grep\n"); // chyba
			return -3;
		default :			// rodic. proces
			close(pipedes[1]);	// zatvorenie vstupu z datovodu
			memset(number,0,NUMBER_SIZE); // string number vynulovany 
			read(pipedes[0],number,NUMBER_SIZE-1); // nacitanie z datovodu
			close(pipedes[0]);	// zatvorenie datovodu
			sscanf(number,"%d",&count); // prevod na cislo
	}
	wait(NULL);
	
	return count;	// vrati zisteny pocet
}
