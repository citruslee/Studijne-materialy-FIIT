/*
* Meno: Rado Orsula
* Kruzok: 2
* Datum: 6.5.2005
* Zadanie: zadanie08c
* Kompilacia: cc pripravne_08c.c -o pripravne_08c
*
* Text zadania:
* Napiste program, ktory vypise vsetkych pouzivatelov prihlasenych 2 a viac
* krat. Na zistenie prihlasenych pouzivatelov pouzite (povinne) vystup
* prikazu who a tento citajte cez ruru.
*
* Syntax:
* zadanie2 [-h]
*
* Format vystupu (na standardny vystup):
* Output: '<pouzivatel> <pocet>'
*
* Bonusove body mozete ziskat ak minimalny hladany pocet prihlaseni bude
* moct byt zadany ako argument programu. (priklad: zadanie2 4).
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
#include <string.h>

#define MAX_USERS 1000
int USER_POINTER = 0;

char USERS[MAX_USERS][19];
int USER_COUNT[MAX_USERS];
int NUMBER = 2;

void Help();
void reset();
void checkThis(char *name);
void output();
int convert(char *number);

void main(int argc, char *argv[]) {
       int o;
       char meno[19];
       char znak;
       int buffsize;
       int index;
       int pipee[2];
       opterr = 0;

       while ((o = getopt(argc, argv, "h")) != -1)
               switch (o) {
                       case 'h':
                               Help();
                               exit(0);
/*      prepinac s jednym parametrom
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

       if(argc > 0) {
               NUMBER = convert(argv[0]);
               argc--;
               argv++;
       }

       if(argc>0) {
               fprintf(stderr, "Error: nespravny pocet argumentov\n");
               exit(1);
       }

       reset();

       if(pipe(pipee)!=0) {
               fprintf(stderr, "Error: ");
               perror("pipe");
       }

       switch(fork()) {
               case -1:
                       fprintf(stderr, "Error: 'fork': zlyhalo volanie jadra operacneho systemu\n");
                       exit(1);
               case 0:
                       close(pipee[0]);
                       close(1);
                       if(dup(pipee[1])==-1) {
                               fprintf(stderr, "Error: 'dup': zlyhalo volanie\n");
                               exit(1);
                       }
                       close(pipee[1]);

                       execlp("who", "who", NULL);
                       fprintf(stderr, "Error: 'execlp': zlyhalo volanie\n");
                       exit(1);
               default:
                       close(pipee[1]);
                       close(0);
                       if(dup(pipee[0])==-1) {
                               fprintf(stderr, "Error: 'dup': zlyhalo volanie\n");
                               exit(1);
                       }
                       close(pipee[0]);
                       while((buffsize=read(0,meno, 17))!=0) {
                               meno[buffsize]='\0';
                               checkThis(meno);
                               while((buffsize=read(0,&znak,1))!=0) {
                                       if(znak=='\n') break;
                               }
                       }

                       output();
       }
}

void reset() {
       int i;
       i=0;
       for(i=0; i<MAX_USERS; i++) {
               USERS[i][0]='\0';
               USER_COUNT[i]=0;
       }
       USER_POINTER=0;
}

int convert(char *number) {
       int i;
       int value=0;
       for(i=0; i< strlen(number); i++) {
               value*=10;
               value+=(number[i]-'0');
       }
       return value;
}

void checkThis(char *meno) {
       int i;
       int found;
       found=0;

       //fprintf(stderr, "Debug: %s\n", meno);
       for(i=0; i<MAX_USERS; i++) {
               if(strcmp(meno, USERS[i])==0) {
                       USER_COUNT[i]++;
                       found=1;
               }
       }
       if(found==0 && USER_POINTER < MAX_USERS) {
               strcpy(USERS[USER_POINTER], meno);
               USER_COUNT[USER_POINTER]++;
               USER_POINTER++;
       }
}

void output() {
       int i;
       for(i=0; i<MAX_USERS; i++) {
               if(USER_COUNT[i]>=NUMBER) {
                       printf("%s\n",USERS[i]);
               }
       }
}

void Help() {
/* Sem treba dopisat help */
       printf("pripravne08c (C) Rado Orsula\n\n");
       printf("Usage: <meno_programu>\n\n");
}
