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

//* POSTUP PRI RIESENI *********************************************************
// Text zadania (a aj spravanie vysledneho programu) je velmi podobne zadaniu
// cislo 12 uvedenemu v subore karas_12c.c V podstate vtedy sme hladali takych
// pouzivatelov, ktori mali spustenych menej ako 4 procesy, teraz budeme hladat
// takych, ktori ich maju spustene viac ako 4. Stacilo by teda zmenit operator
// porovnania v subore karas_12c.c. V tomto rieseni (pouzili sme opet tabulku
// pouzivatelov) su operacie pre tabulku pouzivatelov navrhnute trochu inak.
// V porovnani s riesenim karas_12c.c v tomto programe autor oddelil testovanie
// argumentov programu od samotneho spracovania, co mozno hodnotit z hladiska
// programatorskeho stylu ako krajsie riesenie, a nepouziva tolko globalnych
// premennych (funkcie programu nemaju tolko vedlajsich efektov, teda su
// vseobecnejsie napisane - opet ukazka krajsieho programatorskeho stylu ...)
 
//* DEKLARACIE *****************************************************************
// maximalna dlzka tabulky pouzivatelov, ktoru budeme alokovat staticky
#define UserCount 200

// polozka tabulky pouzivatelov, ktori maju spusteny aspon jeden proces.
// O kazdom pouzivatelovi si budeme pametat jeho meno (login, vyhradili sme pre
// meno pouzivatela 25 znakov, co je viac nez dost ... ) a pocet spustenych
// procesov ...
typedef struct us
{
    char UserName[25];
    int ProcNo;
} User;

// zadefinujeme si tabulku pouzivatelov. Bude pozostavat z pola poloziek o
// pouzivateloch ...
int LastUserIndex= 0;
User UserTab[UserCount];

//* PROTOTYPY POMOCNYCH FUNKCII ************************************************
// pomocna funkacia na vypisanie strucneho helpu
void Help();
// spracovanie programu. Vypise tych pouzivatelov, ktori maju spustenych viac ako
// definovany pocet procesov (riesime aj bonusovu cast ...)
void CommandPs(int);

// operacie s tabulkou. Budeme testovat, ci pouzivatel so zadanym menom existuje
// v tabulke ...
int IsInTable(char *);
// ... a ak tam este nie je, budeme ho (zrejme) chciet do tabulky zaradit ...
int AddUser(char * );
 
//* IMPLEMENTACIA **************************************************************
// v hlavnom programe spracujeme argumenty programu a podla potreby vyvolame
// spravnu funkciu pre spracovanie ... 
int main(int argc, char * argv[])
{
    // limit poctu procesov pre vypisovaneho pouzivatela. Standardne budeme
    // vypisovat tych pouzivatelov, ktori maju spustene viac ako styri procesy
    // (teda ak to pouzivatel neuvedie inak v argumentoch programu)
    int MinProc= 4;

    if(!strcmp(argv[1],"-h")){
        // ak pouzivatel zadal prepinac -h, zobazime mu strucnu napovedu
        Help();
        exit(0);
    }
    
    // v opacnom pripade ocakavame v argumentoch jedine cislo, ktore definuje
    // limit poctu procesov ...
    if(argc == 1){
        if(! sscanf(argv[1],"%d",&MinProc)){
            // kniznicna funkcia *scanf vracia pocet uspesne spracovanych
            // a priradenych hodnot definovanych formatovacim retazcom. Ak
            // sa jej nepodarilo precitat / ulozit cislo z prveho argumentu
            // asi ma (to cislo) zly format ...
            fprintf(stderr, "Error: 'Nespravny argument ( pozri help 'koncz_13c -h).\n");
            exit(1);
        }
    }
    else{
        // ine argumenty spracovat nevieme. Pouzivatel sa zrejme pri spustani
        // programu pomylil
        fprintf(stderr, "Error: 'Nespravny pocet argumentov ( pozri help 'koncz_13c -h).\n");
        exit(1);
    }
 
    // a nakoniec vykoname spracovanie (vyhladame mena pouzivatelov s pozadovanou
    // vlastnostou) ...
    // printf("Debug: 'Pocet minimalnych procesov: %d.\n",MinProc);
    CommandPs(MinProc);
  
    return 0;
}  

//******************************************************************************
// vypis strucneho helpu pre pouzivatela
void Help()
{
    printf("koncz_13c (c) Richard Koncz\n");
    printf("Usage: koncz_13c [-h] [n]\n");
    printf("       -h vypis tohto helpu\n");
    printf("       n  minimalny pocet spustenych procesov pre pouzivatela,\n");
    printf("          ktory sa ma vypisovat\n");
}

//******************************************************************************
// Implementacia zakladnej funkcie programu (hladanie mien pouzivatelov podla
// specifikovaneho kriteria). Funkcia main ju vlastne iba 'obaluje' = 
// zabezpecuje transformaciou standardneho programoveho rozhrania so sellom
//  - prikazoveho riadku - na standardne rozhrania programovacieho jazyka C
// - volanie funkcie.
// spracovanie zrealizujeme spustenim pomocneho procesu, jeho prepojenim s 
// rodicovskym procesom pomocou datovodu, vykonanim prikazu ps v detskom
// procese a spracovanim jeho vystupu v rodicovi
void CommandPs(int ProcCount)
{
    // PID detskeho procesu
    int pid;
    // deskriptory pre datovod, ktorym prepojime rodicovsky proces s procesom
    // v ktorom pobezi prikaz ps
    int pipefds[2];
    // pomocny indecx (do tabulky)
    int index;
    // 
    FILE *f;
    // vyrovnavajuca pamet na spracovanie 
    char line[150];         
    char UserName[25];          

    // otvorime datovod
    if(pipe(pipefds) < 0){
        printf("Error: 'Nastala chyba pri vytvarani pipy.'\n");
        exit(1);
    }
    
    // a vytvorime detsky proces. Dieta obsahuje kopie deskriptorov rodica
    // ktore sa viazu k tym istym suborom (zdrojom operacneho systemu). Takymto
    // sposobom zabezpecime zdielanie datovodu medzi procesmi
    if((pid = fork()) < 0){
    	// zaporna navratova hodnota volania indikuje chybu (problem) pri
    	// vykonavani, detsky procesa sa nespustil
        printf("Error: 'Nastala chyba pri vytvarani dcerskeho procesu.'\n");
        exit(1);
    }
   
    if(pid == 0){
	    // v detskom procese vrati fork hodnotu 0
        // uzatvrieme subor priradeny k standardnemu vystupu procesu
        close(1);
        // na jeho miesto zduplikujeme vstup datovoru
        if(dup(pipefds[1]) < 0){
              printf("Error: 'Nastala chyba pri duplikovani handle.'\n");
              exit(1);
        }
        // a zavrieme nepotrebne deskriptory
        // (vstupny deskriptor sme si prave zduplikovali)
        close(pipefds[1]);
        // (v dietati staci do datovodu iba zapisovat, vystup z datovodu
        // zavrieme tiez)
        close(pipefds[0]);

        // a spustime prikaz ps
        execl("/bin/ps","ps","-aux",NULL);
        // vykonavanie sa z exec vrati len v pripade chyby ...
        printf("Error: 'Nastala chyba pri spracovani prikazu 'ps'.'\n");
        exit(1);
    }
 
    // v rodicovskom procese vrati uspesne volanie fork PID dietata
 
    // printf("Debug: 'Pocet procesov: %d.\n",ProcCount);
    // v rodicovskom procese budeme z datovodu naopak len citat, 
    // vstupny deskriptor (na zapisovanie) teda zavrieme
    close(pipefds[1]);
    
    // kvuoli pohodlnejsiemu spracovaniu si vystupny deskriptor datovodu
    // transformujeme na stream (aby sme mohli pouzivat funkcie fgets,
    // fscanf namiesot read ...)
    if((f= fdopen(pipefds[0],"r")) == NULL){ 
        printf("Error: 'Nastala chyba pri prekonvertovavani handle z int na FILE *.'\n");
        exit(1);
    }

    // budeme citat z datovodu riadky obsahujuce udaje o jednotlivych
    // procesoch systemu. Pouzitie cyklu do nie je prilis vhodne - pretoze
    // ukoncovacia podmienka je uvedena az nakonci cyklu, navyse sa velmi
    // pletie s cyklom while (klauzula while (podmienka); ktora ukoncuje
    // cyklus do oznacuje aj prazdny cyklus while), v programe karas_12c.c
    // je uvedene krajsie riesenie ....
    do{
        // nacitame riadok z vystupu programu ps (nasho detskeho procesu)
        if(fgets(line,150,f) == NULL){
            if(feof(f) == 0){
                printf("Error: 'Nastala chyba pri nacitavani z rury.'\n");
                exit(0);
            }
            else{
                break;
            }
        }
           
        // kazdy riadok vystupu prikazu obsahuje informaciu o prave jednom
        // procese, okrem prveho riadku, v ktorom sa nachadzaju titulky
        // k vypisovanym stlpcom. Budeme testovat, ci riadok obsahuje titulok
        // 'USER'. Nevyhodou takehoto testovania je, ze odfiltruje aj riadky
        // o procesoch, ktorych vlastnik je pouzivatel s loginom 'USER' alebo
        // s menom 'USER' - aj ked je to dost nepravdepodobne. Krajsim riesenim
        // by bolo jednoducho preskocit prvy riadok vypisu
        if (strstr(line,"USER")){
            continue;
        }
    
        // vo vystupe z programu ps -u sa meno vlastnika nachadza v prvom
        // stlpci
        sscanf(line,"%s",UserName);        // meno pouzivatela
    
        // ak sa v tabulke nachadza zaznam o pouzivatelovi s precitanym menom
        if((index= IsInTable(UserName)) >= 0){
            //printf("Debug: User '%s' je v tabulke pod indexom '%d'.\n",UserName,index);
            // zvysime pocet jeho procesov
            UserTab[index].ProcNo++;
            //printf("Debug: Stav user %s - %d.\n",UserTab[index].UserName,UserTab[index].ProcNo);
        }
        else{
            // inak sa ho pokusime pridat do tabulky ...
            //printf("Debug: User '%s' nie je v tabulke.\n",UserName);
            if((index= AddUser(UserName)) == -1){
                printf("Error: 'Tabulka uzivatelov je plna!!!'\n");
                exit(1);
            }
            //printf("Debug: Pridal sa novy user '%s' s indexom '%d' (%s,%d) (Last: %d).\n",UserName,index,UserTab[index].UserName,UserTab[index].ProcNo,LastUserIndex);
        }
    }while(! feof(f));
 
    // po spracovani vystupu programu ps zatvorime aj druhu stranu datovodu
    // (datovod uz nepotrebujeme)
    fclose(f);
    
    // a nakoniec prejdeme postupne celu tabulku pouzivatelov a vypiseme mena
    // tych pouzivatelov, ktorym sme napocitali viac procesov ako stanoveny
    // minimalny pocet
    for(index= 0; index < LastUserIndex; index++){
        if(UserTab[index].ProcNo > ProcCount){
            printf("Output: '<%s> <%d>'\n",UserTab[index].UserName,UserTab[index].ProcNo); 
        }
    }  
}

//******************************************************************************
// test, ci sa pouzivatel so zadanym menom nachadza v tabulke. Ak pouzivatela
// v tabulke najdeme, vratime index najdeneho prvku tabulky, ak ho nenajdeme, 
// vratime -1
int IsInTable(char *name)
{
    int i;
    
    // postupne prejdeme vsetky (obsadene) prvky v tabulke
    for(i= 0; i < LastUserIndex; i++){
        //printf("Debug: %d. <%s> ?= <%s> -> %d.\n",i,UserTab[i].UserName,name,strcmp(UserTab[i].UserName,name));
        if((strcmp(UserTab[i].UserName,name)) == 0){
            //printf("Debug: IsIn - %s,%d (%d).\n",name,i,LastUserIndex);
            // prvok s udajmi o pouzivatelovi sme nasli
            return (i);
        }
    }

    // takze smola, mozno nabuduce :) ...
    return -1;
}

//******************************************************************************
// Pridame pouzivatela so zadanym menom do tabulky. Vystupom je index do pola
// po uspesnom pridani pouzivatela, alebo -1, ak nastala chyba (minulo sa volne
// miesto v tabulke)
int AddUser(char *name)
{
    // skontrolujeme teda velkost tabulky
    if(LastUserIndex == (UserCount - 1)){
        return -1;
    }
    
    // ulozime meno pouzivatela, pocet procesov automaticky nastavime na 1
    // (ak by pouzivatel nespustil ziadny proces, ani by sme ho do tabulky
    // nepridavali) ...
    strcpy(UserTab[LastUserIndex].UserName,name);
    UserTab[LastUserIndex].ProcNo= 1;
    //printf("Debug: AddUser - %s (%d)\n",name,LastUserIndex);
    
    // ... a upravime velkost tabulky 
    return LastUserIndex++;
}
