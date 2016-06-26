/* Meno: Tomas Karas
 * Kruzok: odborne praktikum - OS
 * Datum:  
 * Zadanie: zadanie12c
 * Kompilacia: cc zadanie12c.c -o zadanie12c
 *
 * Text zadania:
 * Napiste program, ktory vypise vsetkych pouzivatelov, ktori maju spustenych
 * menej ako 4 procesy.
 * Na zistenie spustenych procesov pouzite (povinne) vystup 
 * prikazu 'ps -Af' a tento citajte cez ruru.
 *    
 * Syntax: 
 * zadanie2 [-h] 
 *  
 * Format vystupu (na standardny vystup):
 * Output: '<pouzivatel> <pocet>'
 *    
 * Bonusove body mozete ziskat ak maximalny hladany pocet spustenych procesov
 * bude moct byt zadany ako argument programu. (priklad: zadanie2 7).
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
 * Prikaz ps v systeme Free BSD nema prepinac -A a prepinac -f ma iny vyznam
 * preto som pouzil prepinace -uax. 
 *
 */
 
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define MAXDLZKAMENA 20
   // maximalna dlzka mena pouzivatela
#define VELKOSTTAB 200
   // pocet poloziek v tabulke uzivatelov a ich
   // procesov
#define MAXDLZKARIADKU 100
  // maximalna dlzka riadku citaneho z vystupu
  // prikazu ps

typedef struct _uzivproc
{
 char uzivatel[MAXDLZKAMENA];
 int pocetprocesov;
} uzivproc;

uzivproc tabulka[VELKOSTTAB]; //tabulka pouzivatelov a poctu ich procesov
int pocetobsadenych=0; // pocet obsadenych miest v tabulke
int pipa[2]; // pipe na citanie vystupu z prikazu ps
int pid; // premenna na ulozenie proces id
int maxpocetprocesov=4; // horna hranica poctu procesov
FILE * vstup;
char riadok[MAXDLZKARIADKU]; // riadok precitany z ps
char meno[MAXDLZKAMENA];  // meno uzivatela ziskane z riadku

extern int errno; // ukladanie cisla chyby

int jeuzivvtab( char * ); // funkcia zisti ci je dany uzivatel v tabulke
int pridajuziv( char * ); // pridanie uzivatela do tabulky
void pridajprocesuziv( int ); // pridanie procesu uzivatelovi
void vypishelp(void); // vypise help

// ------------------  main -----------------------
// argc pocet argumentov na prikazovom riadku
// argv pole obsahujuce tieto argumenty
// prvy argument je meno spusteneho suboru (zadanie12)

int main(int argc, char * argv[])
{
 int c;
 // ziskanie argumentov z prikaz riadku
 for ( c=1; c<argc; c++)
 {
  if ( strcmp(argv[c],"-h") == 0 ) // strcmp porovna dva retazce ak sa
  {
	// zhoduju vrati 0
 	// ak je na prikaz. riadku argument -h tak vypise help
   vypishelp();
   exit(0); // a skonci
  }
  if ((sscanf(argv[c],"%d",&maxpocetprocesov)) < 1 ) // sscanf cita retazec
  {
	// a konvertuje ho do stanoveneho formatu (%d - int)
	// vrati pocet uspesnych konverzii (aspon 1)
	// ak nie tak nespravny argument
   fprintf(stderr,"Nespravny parameter %s\n",argv[c]);
	//vypise help a skonci
   vypishelp();
   exit(0);
  }
 }
	// vytvovenie pipy-rury na prenos udajov mezi procesmi
 if ( pipe(pipa) < 0 )
 {
	// ak vznikne chyba tak pipe vrati zaporne cislo
  perror("pipe");
	// vypis chyby a koniec
  exit(1);
 }
 // vytvorenie dcerskeho procesu
 // ak vznikne chyba fork vrati zaporne cislo
 if ((pid = fork()) < 0 )
 {
  perror("fork");
  exit(1);
 }
 // dcersky proces ma pid nastavene na 0
 if ( pid == 0 )	// child process
 {
  close(1); // uzatvorenie stdout
  // dup duplikuje vstup pipy
  // duplikovany handle zapise na prvy volny t.j. stdout
  // ak vznikne chyba vrati zaporne cislo
  if ( dup(pipa[1]) < 0 )
  {
   perror("dup");
   exit(1);
  }
  close(pipa[1]);
  close(pipa[0]);
  // exec spusti prikaz ps
  execl("/bin/ps","ps","-uax",NULL);
  perror("exec");
  exit(1);
 }
 
 // rodicovsky proces dostane pid dcerskeho procesu != 0
 
 close(pipa[1]);
 // prekonvertovanie handla (int) na (FILE *)
 vstup=fdopen(pipa[0],"r");
 if ( vstup == NULL )
 {
  perror("fdopen");
  exit(1);
 }
 do
 {
  // nacitanie riadku z pipy
  if ( fgets(riadok,MAXDLZKARIADKU,vstup) == NULL )
  // test ci vznikla chyba pri citani
  // koniec suboru alebo nieco ine
   if ( feof(vstup) == 0 )
   {
    perror("fgets");
    exit(0);
   }
   else
    break;
  // ziskanie prveho retazca z precitaneho riadku ( meno uzivatela )
  sscanf(riadok,"%s",meno);
  // odfiltrovanie prveho riadku tabulky ( USER PID %CPU %MEM ...)
  if ( strcmp(meno,"USER") == 0 )
   continue;
  // test ci je uz uzivatel v tabulke
  if ((c=jeuzivvtab(meno)) > 0 )
  // ak ano tak mu pridame proces
   pridajprocesuziv(c);
  else
  {
  // ak nie tak ho pridame do tabulky
  // a pridame mu proces
   if ((c=pridajuziv(meno)) < 0 )
   {
    fprintf(stderr,"pridajuzivatela : Chyba plna tabulka\n");
    exit(1);
   }
   pridajprocesuziv(c);
  }
  // robime dokial nie je koniec suboru
 } while( feof(vstup) == 0 );
 
 // uzatvorenie jednej strany pipy
 // druhu strana sa uzatvori pri skonceni dcerskeho procesu a tym sa
 // pipa zrusi
 fclose(vstup);
 // prehladavanie tabulky a uzivatelov, ktorych pocet procesov je < ako
 // max pocet procesov
 for ( c=0; c<pocetobsadenych; c++)
  if ( tabulka[c].pocetprocesov < maxpocetprocesov )
   printf("%s\t\t%d\n",tabulka[c].uzivatel,tabulka[c].pocetprocesov); 
 
 return 0;
}  //-------------- koniec main ------------------------

//---------- int jeuzivvtab ( char * ) ------------------
// hlada uzivatela v tabulke
// vstup: meno hladaneho uzivatela
// vystup: ak najde tak pozicia uziv v tabulke <1.. >
//         ak nie tak -1
int jeuzivvtab( char * meno )
{
 int a;
 
 for ( a=0; a<pocetobsadenych; a++)
  if ( strcmp(tabulka[a].uzivatel,meno) == 0 )
   return (a+1);

 return -1;	//nie je v tabulke
}
//----------- int pridajuziv ( char * ) --------------------
// prida uzivatela do tabulky
// vstup: meno uzivatela
// vystup: -1 ak je tabulka plna alebo
//         poziciu na ktoru bol uziv pridany <1.. >
// pocet procesov pridaneho pouzivatela je nastaveny na 0
int pridajuziv( char * meno )
{
 if ( pocetobsadenych == VELKOSTTAB )
  return -1;  //	plna tabulka
 
 strcpy(tabulka[pocetobsadenych].uzivatel,meno);
 tabulka[pocetobsadenych].pocetprocesov=0;
 pocetobsadenych++;
 return pocetobsadenych;
}
//---------- void pridajprocesuziv ( int ) ---------------
// prida proces uzivatelovi
// vstup: pozicia uzivatela v tabulke <1..>
// vystup: nic
void pridajprocesuziv( int b )
{
 tabulka[b-1].pocetprocesov++;
}
//-------------void vypishelp(void) ----------------------
// vypise help
void vypishelp( void )
{
 printf("Zadanie 12c (C) Tom\n");
 printf("Usage: zadanie12c [n] [-h]\n");
 printf("Vypise vsetkych pouzivatelov, ktori maju spustenych menej\n ako n procesov.\n");
 printf("Ked nie je n zadane tak menej ako 4 procesy\n");
} 
 