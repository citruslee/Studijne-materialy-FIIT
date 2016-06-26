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


//* POSTUP PRI RIESENI *********************************************************
// Po spusteni programu skontrolujeme parametre. Vytvorime novy proces a jeho
// vystup presmerujeme cez datovod do programu, kde ho budeme spracovavat.
// Potom vo vytvorenom dietati spustime zelany program ps s prepinacmi -axu
// ktory vypise na standardny vystup (po presmerovani do naseho datovodu) udaje
// o vsetkych systemovych procesoch (prepinac a), aj tie, ktore nemaju prideleny
// terminal (prepinac x), vystup ma urcity presne specifikovany tvar (meno
// vlastnika procesu na nachadza v prvom stlpci (prepinac u). Vystup programu
// budeme postupne citat, a priebezne pocitat vyskyty mien vlastnikov
// jednotlivych procesov (v kazdom riadku su informacie prave o jednom procese).
// Na tento ucel si vytvorime tabulku, v ktorej budeme udrziavat informacie
// jednak o precitanych menach vlastnikov a jednak o pocte ich vyskytov.


//* DEKLARACIE *****************************************************************
// maximalna dlzka mena pouzivatela (... obycajne je dlzka mena pouzivatela
// ohranicena na 8 znakov ...)
#define MAXDLZKAMENA 20
// pocet poloziek v tabulke pouzivatelov (budeme ju alokovat staticky, takze jej
// dlzku musime zhora nejako ohranicit. 200 bude stacit - ani na decefe nebyva
// naraz viac ludi ako 80; ale keby aj, nie je problem tabulku prepisanim tejto
// konstanty podla potreby zvecsit) ... 
#define VELKOSTTAB 200
// maximalna dlzka riadku citaneho z vystupu prikazu ps (ps -axu ma riadky
// dokonca este kratsie, ale pre istotu ... :)
#define MAXDLZKARIADKU 100

// Polozka tabulky pouzivatelov bude uchovavat retazec s menom vlastnika
// procesu a pocet procesov tohto pouzivatela
typedef struct _uzivproc
{
    char uzivatel[MAXDLZKAMENA];
    int pocetprocesov;
} uzivproc;

// Tabulku pouzivatelov si zadefinujeme ako globalnu premennu ...
uzivproc tabulka[VELKOSTTAB];
// Budeme si udrziavat pocet vyplnenych poloziek v tabulke (tabulka zatial
// ziadne neobsahuje) ...
int pocetobsadenych=0;
// dalej datovod, pomocou ktoreho budeme citat informacie z pomocneho detskeho
// procesu (prikaz ps). Datovod ma dva konce (deskriptory), jeden vstupny (s
// indexom 1) a jeden vystupny (s indexom 0) ...
int pipa[2];
// id pomocneho dietskeho procesu ...
int pid;
// horny limit poctu procesov pouzivatelov, ktorych budeme zobrazovat na
// vystupe (standardne to bude 4) ...
int maxpocetprocesov=4;
// kvuoli pohodlnejsiemu citaniu z datovodu (budeme citat pomocou kniznicnej
// funkcie scanf)
FILE * vstup;
// vyrovnavacia pamet na precitany riadok z prikazu ps
char riadok[MAXDLZKARIADKU];
// vyrovnavacia pamet na meno pouzivatela
char meno[MAXDLZKAMENA];

//* PROTOTYPY POMOCNYCH FUNKCII ************************************************
// Udajovy typ pozostava z dvoch casti. Prvu cast tvori mnozina hodnot, tu druhu
// operacie nad tymito hodnotami. Zaviedli sme si udajovy typ tabulka. Jeho
// hodnoty su specifikovane jeho pametovou reprezentaciou (pole prvkov, kazdy
// prvok ma dve polozky - meno pouzivatela a pocet jeho procesov). Potrebujeme
// este operacie - zmysluplne vypocty, ktore transformuju hodnoty udajoveho typu 
// (aj na iny udajovy typ - spritupnenie nejakeho elementu, pretypovanie, ...).
// Budeme potrebovat test, ci v tabulke existuje zaznam o pouzivatelovi so
// specifikovanym menom ...
int jeuzivvtab( char * );
// ... dalej operaciu, ktora prida noveho pouzivatela (so zadanym menom)
// do tabulky ...
int pridajuziv( char * );
// ... a operaciu pomocou ktorej zvysime pocet procesov pre pouzivatela, ktoreho
// udaje sa nachadzaju v prvku pola (reprezentujuceho nasu tabulku)
// so zadanym indexom
void pridajprocesuziv( int ); 

// pomocna funkcia na vypis helpu
void vypishelp(void);


//* IMPLEMENTACIA **************************************************************
// v hlavnej funkcii sa nachadza cely. Pozostava z dvoch zakladnych casti -
// kontrola parametrov a samotne spracovanie, ktore pozostava vytvorenia detskeho
// procesu, prepojenia procesov pomocou datovodu, spustenia prikazov ps a 
// spracovania jeho vystupu. 
int main(int argc, char * argv[])
{
    // index spracovavaneho argumentu programu
    int c;
    
    // cast spracovanie argumentov. Argument s indexom 0 obsahuje meno
    // programu, ten preskocime
    for ( c=1; c<argc; c++)
    {
        if ( strcmp(argv[c],"-h") == 0 ) 
        {
            // ak sme narazili na prepinac -h, zobrazime strucny help a skocime
            vypishelp();
            exit(0);
        }
        // Pokusime sa spracovat aj zvysne parametre. Prikaz sscanf vracia pocet
        // uspesne spracovanych poloziek. Ocakavame spracovanie jedinej polozky
        // - cisla, ktore obmedzuje zhora pocet procesov pouzivatelov, o ktorych
        // informacie budeme spracovavat
        if ((sscanf(argv[c],"%d",&maxpocetprocesov)) < 1 )
        {
            // ak sa nam nepodarilo spracovat ani tu jedinu polozku, argument
            // neobsahuje cislo 
            fprintf(stderr,"Error: nespravny parameter %s\n",argv[c]);
            exit(1);
        }
    }
    
    // ... este by sme mali skontrolovat pocet parametrov (okrem cisla
    // limitujuceho pocet procesov pre jedneho pouzivatela uz neocakavame
    // ziadny iny argument)
    
    // cast spracovanie programu - spustenie noveho procesu, vykonanie zelaneho
    // propgramu a prepojenie pomocou datovodu je zakladna zrucnost, ktoru by
    // ste mali zvladnut, aby ste uspesne vyriesili zadanie. Je to vo vecsine
    // zadani rovnake (az na meno prikazu a heho parametre) ...

    // vytvorime si datovod na prenos udajov mezi procesmi. Vstupom volania je
    // pole obsahujuce miesto na oba deskriptory datovodu. Ak je uspesne,
    // vracia hodnotu 0, inak (v pripade chyby) hodnotu -1
    if ( pipe(pipa) < 0 )
    {
        fprintf(stderr,"Error: chyba pri vytvarani datovodu\n");
        exit(1);
    }
    
    // dalej vytvorime detsky proces. Zaporna navratova hodnota indikuje
    // volajucemu procesu nejaky problem ...
    if ((pid = fork()) < 0 )
    {
        fprintf(stderr,"Error: neda sa vytvorit detsky proces\n");
        exit(1);
    }
    // v detskom procese vrati volanie fork hodnotu 0 ...
    if ( pid == 0 )
    {
        // v dietati napojime standardny vystup na vstup datovodu. Najskor
        // zatvorime subor napojeny na standardny vystup - nebudeme ho uz
        // dalej potrebovat. 
        close(1);
        // Pomocou volania dup zduplikujeme vstupny deskriptor datovodu.
        // Volanie si pre novy deskriptor alokuje volne miesto v tabulke
        // deskriptorov suborov procesu s najnizsim indexom. Kedze sme
        // pred chvilou zatvorili deskriptor (subor) s indexom 1, dup alokuje
        // pre zduplikovany deskriptor miesto prave s tymto indexom. Tymto
        // sa vstup datovodu stal novym standardnym vystupom dietata.
        // Po uspesnom vykonani vracia funkcia hodnotu 0, inak hodnotu -1
        if ( dup(pipa[1]) < 0 )
        {
            fprintf(stderr,"Error: chyba pri presmerovavani vystupu\n");
            exit(1);
        }
        
        // zatvorime oba deskriptory datovodu. V dietati nebudeme z datovodu
        // citat a vstup sme si prave zduplikovali ...
        close(pipa[1]);
        close(pipa[0]);
        
        // volanim exec spustime prikaz ps (volania exec* su blizsie vysvetlene
        // v subore cernansky_1c.c)
        execl("/bin/ps","ps","-uax",NULL);
        // ak volanie exec uspeje, vykonavanie programu sa sem nedostane (do
        // pameti sa zavedie obraz programu ps a zacne sa vykonavat jeho kod)
        // ak sa teda v tejto casti ocitneme, znamena to, ze niekde musela
        // nastat chyba ...
        fprintf(stderr,"Error: nepodarilo sa spustit program ps\n");
        exit(1);
    }
 
    // inak sa jedna o rodicovsky proces. Navratovou hodnotou volania fork je
    // v tomto pripade PID vytvoreneho dietata

    // zatvorime si vstup do datovodu - v rodicovi budeme z datovodu iba citat
    close(pipa[1]);
    // aby sa nam phodlnejsie spracovaval vystup datovodu, transformujeme si
    // ho na stream (funkcia fscanf ponuka viac moznosti a pohodlnejsie
    // spracovanie suboru). Z vystupu budeme samozrejme iba citat ...
    vstup = fdopen(pipa[0],"r");
    if ( vstup == NULL )
    {
        fprintf(stderr,"Error: chyba pri otvarani suboru\n");
        exit(1);
    }

    // spracovanie vystupu prikazu ps (spusteneho ako detsky proces) a zratanie
    // poctu procesov pre jednotlivych pouzivatelov

    // budeme z datovodu citat riadky tak dlho, ako to len pojde. Ak narazime
    // na koniec riadku alebo nastane chyba, kniznicna funkcia fgets vrati
    // nulovy smernik, inak vracia ukazovatel na precitany retazec
    while ( fgets(riadok,MAXDLZKARIADKU,vstup) != NULL )
    {
        // vo vypise programu ps s prepinacmi -axu sa meno vlastnika procesu
        // nachadza ako prve slovo
        sscanf(riadok,"%s",meno);
        
        // prvy riadok vypisu programu ps obsahuje vzdy titulok k vypisovanym
        // stlpcom. Ten musime zahodit, lebo sa nejedna o meno pouzivatela.
        // Mozme to robit porovnanim s retazcom "USER", ktory je titulkom
        // ku stlpcu s menom vlastnika, alebo krajsie - ze si zavedieme pomocnu
        // premennu, v ktorej si budeme pametat, ci citame prvy riadok vystupu -
        // vtedy ho zahodime, alebo niektory z dalsich
        if ( strcmp(meno,"USER") == 0 )
            continue;

        // skontrolujeme, ci sa nacitany pouzivatel nenachadza v tabulke ...
        if ((c=jeuzivvtab(meno)) < 0 )
            // ... v takom pripade sa ho pokusime do tabulky zaradit ...
            if ((c=pridajuziv(meno)) < 0 )
            {
                fprintf(stderr,"Error: plna tabulka pouzivatelov\n");
                exit(1);
            }

        // ... a zvysime pocet jeho procesov
        pridajprocesuziv(c);
    }

    // funcia fgets mohla vratit hodnotu NULL z dvoch dvuovodov: narazili sme
    // na koniec suboru, alebo nastala pri citani nejaka chyba - co by sme mali
    // osetrit ...
    if ( feof(vstup) == 0 )
    {
        fprintf(stderr,"Error: chyba pri citani z datovodu\n");
        exit(1);
    }
 
    // teraz uz datovod nepotrebujeme, zatvorime aj jeho vystup (prepojili
    // sme ho na standardny vstup rodicovskeho procesu) ...
    fclose(vstup);
    
    // prehladame tabulku pouzivatelov, a udaje tych poloziek, v ktorych pocet
    // procesov je mensi ako maximalny limit zobrazime v pozadovanom tvare na 
    // standardny vystup programu ...
    for ( c=0; c<pocetobsadenych; c++)
        if ( tabulka[c].pocetprocesov < maxpocetprocesov )
            printf("Output: '%s %d'\n",tabulka[c].uzivatel,tabulka[c].pocetprocesov); 
 
    return 0;
}

//******************************************************************************
// operacia vyhladania pouzivatela podla zadaneho mena v tabulke. Vrati index
// najdenej polozky (tentokrat cislujeme od 1) alebo -1, ak sme pouzivatela so
// zadanym menom nenasli
int jeuzivvtab( char * meno )
{
    // index prvku v tabulke pri prehladavani
    int a;

    // prejdeme postupne vsetky prvky v tabulke. Musime si uvedomit, ze tabulka
    // moze obsahovat aj menej prvkov nez je jej staticka dlzka - aktualnu
    // dlzku tabulky sme si uchovali v globalnej premennej pocetobsadenych
    for ( a=0; a<pocetobsadenych; a++ )
        if ( strcmp(tabulka[a].uzivatel,meno) == 0 )
            // pouzivatela sme v tabulke nasli
            return (a+1);

    // ani po prejdeni vsetkych poloziek v tabulke sme pouzivatela so zadanym
    // menom nenasli ...
    return -1;
}

//******************************************************************************
// operacia pridania pouzivatela so zadanym menom do tabulky. Vystupom funkcie
// je index pridaneho (noveho) prvku v tabulke, ak bola operacia uspesne
// vykonana (indexujeme od 1), alebo -1 ak nastala chyba (v tabulke uz nebolo
// miesto)
int pridajuziv( char * meno )
{
    // skontrolujeme dlzku tabulky ...
    if ( pocetobsadenych == VELKOSTTAB )
        return -1;  //    plna tabulka

    // do noveho prvku tabulky (prvky pridavame na koniec pola) si ulozime meno
    // pouzivatela, a pocet procesov mu nastavime na 0
    strcpy(tabulka[pocetobsadenych].uzivatel,meno);
    tabulka[pocetobsadenych].pocetprocesov=0;
    
    // upravime dlzku tabulky - prave sme pridali novy prvok 
    pocetobsadenych++;
    return pocetobsadenych;
}

//******************************************************************************
// v zazname o pouzivatelovi specifikovanym indexom do tabulky pouzivatelov
// zvysime pocet procesov o 1. Index cislujeme od 1 ...
void pridajprocesuziv( int b )
{
    tabulka[b-1].pocetprocesov++;
}

//******************************************************************************
// vypise kratky help pre pouzivatela
void vypishelp( void )
{
    // o efektivite prikazu printf sme diskutovali v programe cernansky_1c.c
    printf("Zadanie 12c (C) Tom\n");
    printf("Usage: zadanie12c [n] [-h]\n");
    printf("Vypise vsetkych pouzivatelov, ktori maju spustenych menej\n ako n procesov.\n");
    printf("Ked nie je n zadane tak menej ako 4 procesy\n");
} 
