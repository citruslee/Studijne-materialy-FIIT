/*
 * Meno: Tomas Karas
 * Kruzok: odborne praktikum - OS
 * Datum:  
 * Zadanie: zadanie32c
 * Kompilacia: cc zadanie32c.c -o zadanie32c
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
 * Pre citanie a zapisovanie z/do pipy nepouzivam systemove volania read/write
 * ale funkcie C pre pracu so suborom a funkciu fdopen na prekonvertovanie
 * deskriptora pipy (int) na subor (FILE *)
 */
 
#include <stdio.h>
#include <unistd.h>
 
#define MAXDLZKARIADKU 1024

int pipavvs[2],pipavvy[2],pipamvs[2],pipamvy[2];
//datovody pre vymenu dat medzi rodicovskym a dcerskymi procesmi
int pid; //identifikacia procesu
FILE * f1, * f2; // dva vsupne subory
FILE * vystupv, * vstupv, * vystupm, *vstupm;
int iseof1=0,iseof2=0; // indikacia konca suboru(ov)
char riadok[MAXDLZKARIADKU]; // riadok pre nacitavanie
char low[]="[:lower:]"; // parametre do prikazoveho riadku pre program tr
char upp[]="[:upper:]";

extern int errno;  // obsahuje cislo chyby, ked sa vyskytne

void vypishelp(void);  // funkcia na vypisanie helpu
 
int main(int argc, char *argv[])
{
  if ( argc < 3 ) // ak boli na prikazovom riadku menej ako dva argumenty
  {			// tak vypis help
    vypishelp();
    exit(0);
  }
  if ( strcmp(argv[1],"-h") == 0 ) // ak je poziadavka vypisat help tak ...
  {
    vypishelp();
    exit(0);
  }
  if ((f1=fopen(argv[1],"r")) == NULL ) // otvorenie suboru, ktory bol zadany na prikazovom
  {	// riadku ako prvy (parameter)
    fprintf(stderr,"Error:Nemozem otvorit %s\n",argv[1]);
    exit(1); // ak sa nepodarilo tak chyba
  }
  if ((f2=fopen(argv[2],"r")) == NULL ) // otvorenie suboru, ktory bol zadany na prikazovom
  {	// riadku ako druhy (parameter)
    fprintf(stderr,"Error:Nemozen otvorit %s\n",argv[2]);
    exit(1); // ak sa nepodarilo tak chyba
  }
  if ( pipe(pipavvs) < 0 ) // pipe vytvori datovod (vstup) do programu tr
  {	// ak sa nepodari tak vrati zaporne cislo
    perror("Error:pipe");
    exit(1);
  }
  if ( pipe(pipavvy) < 0 ) // datovod (vystup) z programu tr
  {
    perror("Error:pipe");
    exit(1);
  }
  if ((pid = fork()) < 0 ) // fork vytvori dcersky proces
  {	// ak sa nepodari tak vrati zaporne cislo
    perror("Error:fork");
    exit(1);
  }
  // -----  detsky proces konverzia  lower - > upper  -------
  if ( pid == 0 )
  {
    close(1);
    if ( dup(pipavvs[1]) < 0 )
    {// spojime standardny vystup s vystupom datovodu
      perror("Error:dup");
      exit(1);
    }
    close(0);
    if ( dup(pipavvy[0]) < 0 )
    {// spojime standardny vstup zo vstupom datovodu
      perror("Error:dup");
      exit(1);
    }
    // uzatvorime nepouzite vstupy/vystupy
    close(pipavvs[1]);
    close(pipavvs[0]);
    close(pipavvy[0]);
    close(pipavvy[1]);
    // spustime program tr konverzia male velke
    execl("/usr/bin/tr","tr",low,upp,NULL);
    perror("Error:exec");
    exit(1);
  }
  // rodicovsky proces uzatvori nepouzite vstupy/vystupy 
  close(pipavvs[1]);
  close(pipavvy[0]);
  if ( pipe(pipamvs) < 0 ) // vytvorime datovod (vstup) do programu tr
  {
    perror("Error:pipe");
    exit(1);
  }
  if ( pipe(pipamvy) < 0 ) // datovod (vystup) z programu tr
  {
    perror("Error:pipe");
    exit(1);
  }
  // -----  detsky proces konverzia  upper - > lower  ------------
  if ((pid = fork()) < 0 )
  {
    perror("Error:fork");
    exit(1);
  }
  if ( pid == 0 )
  {
    close(1);
    if ( dup(pipamvs[1]) < 0 )
    {// spojime standardny vystup s vystupom datovodu
      perror("Error:dup");
      exit(1);
    }
    close(0);
    if ( dup(pipamvy[0]) < 0 )
    {// spojime standardny vstup zo vstupom datovodu
      perror("Error:dup");
      exit(1);
    }
    // uzatvorime nepouzite vstupy/vystupy
    close(pipamvs[1]);
    close(pipamvs[0]);
    close(pipamvy[0]);
    close(pipamvy[1]);
    // spustime program tr konverzia velke male
    execl("/usr/bin/tr","tr",upp,low,NULL);
    perror("Error:exec");
    exit(1);
  }
  // rodicovsky proces uzatvori nepouzite vstupy/vystupy   
  close(pipamvs[1]);
  close(pipamvy[0]);
  //---------------   fdopen   -------------------------
  // prekonvertuje deskriptor (int) na stream (FILE *) 
  vystupv=fdopen(pipavvy[1],"w");
  if ( vystupv == NULL )
  {
    perror("Error:fdopen");
    exit(1);
  }
  vstupv=fdopen(pipavvs[0],"r");
  if ( vstupv == NULL )
  {
    perror("Error:fdopen");
    exit(1);
  }
  vystupm=fdopen(pipamvy[1],"w");
  if ( vystupm == NULL )
  {
    perror("Error:fdopen");
    exit(1);
  }
  vstupm=fdopen(pipamvs[0],"r");
  if ( vstupm == NULL )
  {
    perror("Error:fdopen");
    exit(1);
  }
  //nacitame riadky prveho suboru a posleme konverznemu programu
  while ( fgets(riadok,MAXDLZKARIADKU,f1) != NULL )
  {
      fputs(riadok,vystupv);
  }
  //nacitame riadky druheho suboru a posleme konverznemu programu  
  while ( fgets(riadok,MAXDLZKARIADKU,f2) != NULL )
  {
      fputs(riadok,vystupm);
  }
  //uzatvorime vstupne subory
  fclose(f1);
  fclose(f2);
  // a datovody, ktore uz nepouzivame
  fclose(vystupv);
  fclose(vystupm);
  // nacitavame striedavo riadky z jedneho a druheho konverzneho programu (velke/male)
  // a vypisujeme
  while ( iseof1 == 0 || iseof2 == 0 )
  {
    if ( iseof1 == 0 )
    {
      if ( fgets(riadok,MAXDLZKARIADKU,vstupv) != NULL )
        printf("%s",riadok);
      else
        iseof1=1;
    }
    if ( iseof2 == 0 )
    {
      if ( fgets(riadok,MAXDLZKARIADKU,vstupm) != NULL )
        printf("%s",riadok);
      else
        iseof2=1;
    }
  }
  // uzatvorime nepouzivane datovody
  fclose(vstupv);
  fclose(vstupm); 
  return 0;	//  Koniec main
}
//----------------------- vypishelp ------------------------
// vypise help 
void vypishelp(void)
{
  printf("Zadanie 32c (C) Tom\n");
  printf("Pouzite: zadanie32c [-h] subor1 subor2\n");
  printf("Program vypisuje postupne prve, druhe .... riadky z oboch suborov,\n");
  printf(" pricom pismena zo suboru1 skonvertuje na velke a pismena zo suboru2\n");
  printf(" skonvertuje na male.\n");  
}
