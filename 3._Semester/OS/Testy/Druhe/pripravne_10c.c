/*
 * Meno: Michal Samiec
 * Kruzok: 2
 * Datum: 10.12.2005 
 * Zadanie: zadanie10c
 * Kompilacia: cc pripravne_10c.c -o pripravne_10c
 *
 * Text zadania:
 * Napiste program, ktory bude opakovane spustat zadany program prog, pricom
 * od ukoncenia jedneho behu do zaciatku nasledujuceho behu tohto programu 
 * caka sek sekund. Pritom do zadaneho suboru file pridava nasledovne 
 * informacie: standardny vystup programu prog, 
 * pocet prave prihlasenych pouzivatelov
 * v tvare:
 * Users: xx
 * a navratovy kod programu prog v tvare:
 * Return code: xx
 *   
 * Syntax:
 * zadanie2 [-h] sek file prik 
 *    
 * Bonusove body mozete ziskat ak vas program bude spracovavat prikaz 
 * aj s jeho argumentami. 
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
#include <stdlib.h>
#include <sys/types.h>
#include <utmp.h>
#include <string.h>
#include <fcntl.h>

void Help();
char * convert(int i);
int getInt(char *c);

void main(int argc, char *argv[]) {
       int o;
       int pajpa[2];
       char buffer[80];
       int buffsize;
       char **argumenty;
       char *sek;
       char *file;
       char *con;
       FILE *fp;
       int fw;
       struct utmp u;
       int status;
       int i;
       int SEK;

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
       if(argc < 3) {
               fprintf(stderr, "Error: zly pocet argumetnov (vid.help)\n");
               exit(1);
       }

       sek = argv[0];
       argc--;
       argv++;
       SEK = getInt(sek);
       file = argv[0];
       argc--;
       argv++;

       if((argumenty = (char **) malloc((sizeof(char *) * argc) +1))==NULL) {
               fprintf(stderr, "Error: zlyhalo volanie malloc(pravdepodobne malo pamate)\n");
               exit(1);
       }

       for(i=0; i<argc; i++) {
               argumenty[i] = argv[i];
       }
       argumenty[i]=NULL;

       if((fw=open(file, O_RDWR | O_CREAT | O_TRUNC, 0755))==-1) {
               fprintf(stderr, "Error: '%s': nepodarilo sa otvorit subor na zapis\n");
               exit(1);
       }
       while(1) {
               if(pipe(pajpa)!=0) {
                       fprintf(stderr, "Error: zlyhalo volanie pipe\n");
                       exit(1);
               }

               switch(fork()) {
                       case -1:
                               fprintf(stderr, "Error: zlyhalo volanie fork\n");
                               exit(1);
                       case 0:
                               close(pajpa[0]);
                               close(1);
                               if(dup(pajpa[1])==-1) {
                                       fprintf(stderr, "Error: zlyhalo volanie dup\n");
                                       exit(1);
                               }
                               close(pajpa[1]);
                               execvp(argv[0], argumenty);
                               fprintf(stderr, "Error: zlyhalo volanie execvp\n");
                               exit(1);
                       default:
                               close(pajpa[1]);
                               while((buffsize=read(pajpa[0], buffer,80))!=0) {
                                       write(fw, buffer, buffsize);
                               }
                               close(pajpa[0]);
                               if((fp = fopen(_PATH_UTMP, "r")) == NULL) {
                                       fprintf(stderr, "Error: '%s': nepodarilo sa otvorit subor\n", _PATH_UTMP);
                                       perror(_PATH_UTMP);
                               }

                               i=0;
                               while((fread(&u, sizeof(u), 1, fp))!=NULL) {
                                       if(u.ut_name[0]==NULL) continue;
                                       i++;
                               }
                               fclose(fp);

                               write(fw, "Users: ",7);
                               con = convert(i);
                               write(fw, con,strlen(con));
                               write(fw, "\n", 1);
                               free((void *) con);
                               wait(&status);
                               write(fw, "Return code: ", 13);
                               con = convert(status);
                               write(fw, con, strlen(con));
                               free((void *) con);
                               write(fw, "\n", 1);
                               if(sleep(SEK)!=0) {
                                       fprintf(stderr, "Error: 'sleep': zlyhalo volanie\n");
                                       exit(1);
                               }
               }
       }
       close(fw);
}

char *  convert(int i) {
       char *num;
       int mantisa=1;
       int rad=0;
       if(i==0) return "0";
       while((i/mantisa)!=0) {
               mantisa*=10;
               rad++;
       }

       if((num = (char *) malloc((sizeof(char) * rad)+1)) == NULL) {
               fprintf(stderr, "Error: nedostatok pamati\n");
               exit(1);
       }

       num[rad]='\0';
       rad--;
       while(rad>=0) {
               num[rad] = (i%10)+'0';
               i = i/10;
               rad--;
       }
       return num;

}

int getInt(char *c) {
       int i;
       int val=0;
       for(i=0; i< strlen(c); i++) {
               val*=10;
               val += (c[i]-'0');
       }
       return val;
}

void Help() {
/* Sem treba dopisat help */
       printf("pripravne10c.c (C) Michal Samiec\n\n");
       printf("Usage: <meno_programu> <arg1> <arg2> <arg3> ...\n\n");
       printf("   <arg1>: pocet sekund medzi dvoma procesmy\n");
       printf("   <arg2>: vystupny subor\n");
       printf("   <arg3>: program, ktory sa bude spustat\n");
       printf("   <argx>: arguemnty <arg3>\n\n");
}
