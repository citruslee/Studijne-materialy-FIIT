/*
 * Meno: Richard Koncz
 * Kruzok: odborne praktikum - OS
 * Datum:  
 * Zadanie: zadanie13c
 * Kompilacia: cc koncz_13c.c -o koncz_13c
 *
 * Text zadania:
 * Napiste program, ktory vypise vsetkych pouzivatelov, ktori maju spustenych
 * viac ako 4 procesy.
 * Na zistenie spustenych procesov pouzite (povinne) vystup 
 * prikazu 'ps -Af' a tento citajte cez ruru.
 *    
 * Syntax: 
 * zadanie2 [-h] 
 *  
 * Format vystupu (na standardny vystup):
 * Output: '<pouzivatel> <pocet>'
 *    
 * Bonusove body mozete ziskat ak minimalny hladany pocet spustenych procesov
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
 * Riesenie:
 ps -uax| more
 */
 
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define UserCount 200
 	
typedef struct us
{
  char UserName[25];		// dlzka mena 25 znakov
  int ProcNo;			// pocet pocesov
} User;


int LastUserIndex= 0; 		// index posledneho prvku v tabulke
User UserTab[UserCount]; 	// tabulka pre pouzivatelov

void Help();
void CommandPs(int);
int IsInTable(char *);		// zistenie ci je pouzivatel v tabulke
int AddUser(char * ); 		// pridanie noveho pouzivatela do tabulky
 
 
int main(int argc, char * argv[])
{
  int MinProc= 4; 		// minimalny pocet procesov pre vypisovaneho pouzivatela
 
  if(argc == 2){
    if(!strcmp(argv[1],"-h")){
      Help();
      exit(1);
      }
  
     if(! sscanf(argv[1],"%d",&MinProc)){
       printf("Error: 'Nespravny argument ( pozri help 'koncz_13c -h).\n");
       exit(1);
       }
     }
     
  if(argc > 2){    
    printf("Error: 'Nespravny pocet argumentov ( pozri help 'koncz_13c -h).\n");
    exit(1);
    }
 
  // printf("Debug: 'Pocet minimalnych procesov: %d.\n",MinProc);
  CommandPs(MinProc);
  
  return 0;
}  

void Help()
{
  printf("koncz_13c (c) Richard Koncz\n");
  printf("Usage: koncz_13c [-h] [n]\n");
  printf("      -h vypis tohto helpu\n");
  printf("      n  minimalny pocet spustenych procesov pre pouzivatela,\n");
  printf("         ktory sa ma vypisovat\n");
}


void CommandPs(int ProcCount)
{
  int pid,pipefds[2]; 		// pole pre pipu
  int index;			// index v tabulke 			
  FILE *f;
  char line[150]; 		
  char UserName[25];  		

  if(pipe(pipefds) < 0){
    printf("Error: 'Nastala chyba pri vytvarani pipy.'\n");
    exit(1);
    }
    
  if((pid = fork()) < 0){
    printf("Error: 'Nastala chyba pri vytvarani dcerskeho procesu.'\n");
    exit(1);
    }
   
  // Nasleduje if pre dcersky proces
  if(pid == 0){				// child process
    close(1); 				// uzatvorenie standardneho vystupu
    if(dup(pipefds[1]) < 0){		// zduplikovanie citania rury
      printf("Error: 'Nastala chyba pri duplikovani handle.'\n");
      exit(1);
      }
    close(pipefds[1]);			// zatvorenie zapisu rury
    close(pipefds[0]);			// zatvorenia citania rury

    // spustenie prikazu ps
    execl("/bin/ps","ps","-aux",NULL);
      printf("Error: 'Nastala chyba pri spracovani prikazu 'ps'.'\n");
      exit(1);
    }
 
  // kod pre rodicovsky proces
 
  // printf("Debug: 'Pocet procesov: %d.\n",ProcCount);
  close(pipefds[1]);
  
  if((f= fdopen(pipefds[0],"r")) == NULL){  // prekonvertovanie handla (int) na (FILE *)
    printf("Error: 'Nastala chyba pri prekonvertovavani handle z int na FILE *.'\n");
    exit(1);
    }
  
  do{
    if(fgets(line,150,f) == NULL){
      if(feof(f) == 0){
        printf("Error: 'Nastala chyba pri nacitavani z rury.'\n");
        exit(0);
        }
      else{
        break;
	}
      }
           
    if (strstr(line,"USER")){		// odstranevie prveho riadku vypisu ps
      continue;
      }
    
    sscanf(line,"%s",UserName);		// meno pouzivatela
    
    if((index= IsInTable(UserName)) >= 0){	// ak je v tabulke  
//      printf("Debug: User '%s' je v tabulke pod indexom '%d'.\n",UserName,index);
      UserTab[index].ProcNo++;			// zvys pocet procesov
//      printf("Debug: Stav user %s - %d.\n",UserTab[index].UserName,UserTab[index].ProcNo);
      }
    else{
//      printf("Debug: User '%s' nie je v tabulke.\n",UserName);
      if((index= AddUser(UserName)) == -1){
        printf("Error: 'Tabulka uzivatelov je plna!!!'\n");
        exit(1);
        }
      // UserTab[index].ProcNo++;		// zvys pocet procesov
//      printf("Debug: Pridal sa novy user '%s' s indexom '%d' (%s,%d) (Last: %d).\n",UserName,index,UserTab[index].UserName,UserTab[index].ProcNo,LastUserIndex);
      }
    }while(! feof(f));
 
  fclose(f);			// uzavretie jednej strany rury

  // vypis pouzivatelov podla kriteria min poctu procesov
  for(index= 0; index < LastUserIndex; index++){
    if(UserTab[index].ProcNo > ProcCount){
      printf("Output: '<%s> <%d>'\n",UserTab[index].UserName,UserTab[index].ProcNo); 
      }
    }  
}


int IsInTable(char *name)
{
  int i;
  
  for(i= 0; i < LastUserIndex; i++){
//    printf("Debug: %d. <%s> ?= <%s> -> %d.\n",i,UserTab[i].UserName,name,strcmp(UserTab[i].UserName,name));
    if((strcmp(UserTab[i].UserName,name)) == 0){
//      printf("Debug: IsIn - %s,%d (%d).\n",name,i,LastUserIndex);
      return (i);			// vrati index v tabulke
      }
    }  
  
  return -1;				//nie je v tabulke
}

int AddUser(char *name)
{
  if(LastUserIndex == (UserCount - 1)){
    return -1;  			// zaplnena tabulka
    }
    
  strcpy(UserTab[LastUserIndex].UserName,name);
  UserTab[LastUserIndex].ProcNo= 1;
//  printf("Debug: AddUser - %s (%d)\n",name,LastUserIndex);
  
//  LastUserIndex++;
  return LastUserIndex++;
}

 