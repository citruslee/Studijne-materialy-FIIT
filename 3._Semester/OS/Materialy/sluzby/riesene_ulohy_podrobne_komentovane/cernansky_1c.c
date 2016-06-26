/*
 * Meno: Michal Cernansky
 * Kruzok: odborne praktikum - OS
 * Datum: 28.10.1999  
 * Zadanie: zadanie1c
 * Kompilacia: cc cernans_1c.c -o searchpattern
 *
 * Text zadania:
 * Napiste program, 
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
// v sys/syslimits.h je definovana konstanta PATH_MAX,
// ktora hovori o maximalnej dlzke cesty
#include <sys/syslimits.h>


//* KONCEPCIA PROGRAMU *********************************************************
// Program je vhodne rozdelit na niekolko casti. Prva cast bude spracovavat
// prepinace a jednoduche parametre. Prehladanie zvoleneho aresara (najdenie
// regulach suborov a pripadne spracovanie podadresarov) zabezpeci druha cast
// programu. Tretia cast programu zabezpeci prehladanie obsahu suboru pomocou
// prikazu grep (spusti detsky proces, prepoji sa s nim pomocou datovodu, spusti
// grep a precita vysledok).
// Taketo rozvrhnutie zjednodusi aj implementovanie bonusovej casti zadania
// (jednoducho zavolame jadro spracovania pre kazdy dalsi parameter programu,
// pripadne pre podadresar prave spracovavaneho adresara ...)


//* DEKLARACIE *****************************************************************
// velkost riadku na nacitane cislo od grepu
#define NUMBER_SIZE 20


//* PROTOTYPY POMOCNYCH FUNKCII ************************************************
// funkcia na zobrazenie strucneho helpu
void Help();
// funkcia na prehladanie zadaneho adresara dirname na vyskyt retazca pattern
// (jadro spracovania programu)
void SearchDir(char *dirname,char *pattern);
// spocitanie vyskytu pattern-u v plain subore filername
// kladna alebo nulova navratova hodnota funkcie znamena jej uspesne
// vykonanie, zaporna hodnota indikuje chybu pocas vykonavania
int PrintCount(char *filename,char *pattern);

 
//* IMPLEMENTACIA **************************************************************
// v hlavnom programe prehladame, skontrolujeme a spracujeme argumenty programu
void main(int argc, char *argv[]) 
{
    // premenna o sluzi na odlozenie prave spracovavanej volby programu
    int o;
    // i je pomocna premenna, index v cykle
    int i;
    
    // pri prehladavani prepinacov a volieb skriptu budeme pouzivat kniznicu
    // unistd. Na parsovanie argumentov programu (ich syntakticku analyzu) sa
    // pouziva kniznicna funkcia getoptc. Vstupom funkcie su argumenty programu
    // z prikazoveho riadku (ich pocet a zoznam - pole) a zoznam rozpoznavanych
    // volieb (ako retazec). Vracia ascii hodnotu volby, ak sa jej uspesne
    // podarilo prepinac identifikovat, alebo -1, ak nastala nejaka chyba.
    // Funkcia umoznuje spracovavat jednoznakove volby. Ako vedlajsi efekt
    // volania sa nastavuju globalne (externe) premenne optind - urcuje celkovy
    // pocet uspesne spracovanych argumentov programu pocas parsovania;
    // a globalna premanna opterr, ktora obsahuje kod vyskytnutej chyby
    
    // Chyba sa zatial nevyskytla ...
    opterr = 0;
    // program bude reagovat iba na prepinac -h ...
    while ((o = getopt(argc, argv, "h")) != -1)    // prehladavanie vst. arg.
        switch (o) 
        {
            case 'h':
                // ... a v takom pripade vypise strucny help a skonci 
                Help();
                exit(0);
            case '?':
            default:
                // ine rozpoznane volby su neplatne, program skonci s chybou
                fprintf(stderr, "Error: '%c': nespravny prepinac\n", optopt);
                exit(1);
        }
        
    // preskocime spracovane prepinace
    argc -= optind;
    argv += optind;
    
    // a zabezpecime spracovanie zvysnych argumentov programu (su nimi cesta
    // resp. cesty k adresarom, ktore sa maju spracovat, a prehladavaci retazec
    // - pattern; posledny argument). 
    if(!argc)    
    {
        // minimalne by zoznam (pole) argumentov malo obsahovat prehladavaci
        // pattern. Ak neobsahuje ani ten, je to chyba ...
        fprintf(stderr,"Error: chyba retazec\n");
        exit(1);
    }
    if(argc==1)
        // argumentom programu (ktory este nebol spracovany) je iba prehladavaci
        // pattern (v argumente cislo 0), takze budeme prehladavat aktualny
        // pracovny adresar ...
        SearchDir(".",argv[0]);
    else        
        // argumentmi programu su jedna alebo viac ciest a prehladavaci pattern.
        // Prejdeme teda zoznamom ciest (je ich argc - 1) a spracujeme ich spolu
        // s prehladavacim patternom (argument s indexom argc - 1; musime si
        // uvedomit, ze v programovacom jazyku C indexujeme polia od nuly!)
        for(i=0;i<argc-1;i++)
            SearchDir(argv[i],argv[argc-1]);
}

//***************************************************************************** 
// vypisanie strucneho helpu
void Help() 
{
    // pouzivanie printf je fajn, ale dost spomaluje vykonavanie programu
    // (kvuoli komplexnemu spracovaniu formatovacieho retazca). Preto,
    // ak potrebujeme vypisat neformatovany retazec, je omnoho (casovo aj
    // priestorovo) efektivnejsie pouzit volanie puts. 
    // Ale to len tak na okraj ... 
    printf("\n");
    printf("searchpattern  (C) Michal Cernansky\n");
    printf("Usage : searchpattern [-h] [directory1 [dirctory2 [..]]] pattern\n");
    printf("  -h         : vypise help\n");
    printf("  directoryX : nazvy adresarov kde hladat retazec\n");
    printf("               ak nezadane,prehladava aktualny adresar\n");
    printf("  pattern    : hladany retazec\n");
    printf("\n");
}

//*****************************************************************************
// Implementacia zakladnej funkcie programu, funkcia main ju iba 'obaluje' = 
// zabezpecuje transformaciou standardneho programoveho rozhrania so sellom -
// commandline - na standardne rozhrania programovacieho jazyka C - volanie
// funkcie.
// Na tejto urovni sa budeme zaoberat prehladavanim adresarov, zistovanim stavu
// suborov, pristupovych prav, a dalsich veci suvisiacich najme so suborovym
// systemom
void SearchDir(char *dirname,char *pattern)
{
    // handle otvoreneho adresara
    DIR *dp;
    // spracovavana adresarova polozka
    struct dirent *dir;
    // cesta k najdenemu suboru, obmedzime ju na PATH_MAX znakov; 
    // alternativne by sa pamet dala pripadne alokovat aj dynamicky
    // (volania malloc a free)
    char path[PATH_MAX];
    // pocet vyskytov prehladavacieho patternu v regularnom subore
    int count;
    // struktura obsahujuca stav suboru
    struct stat filestat;
    
    // pomocou volania opendir sa pokusime otvorit adresar specifikovany
    // cestou (retazcom znakov), ktora je vstupom volania. Ak sa podari
    // volaniu uspesne otvorit adresar, funkcia nan vrati handle. V opacnom
    // pripade vracia funkcia NULL
    if((dp = opendir(dirname))==NULL)
    {
        fprintf(stderr,"Error: '%s': chyba pri otvarani adresara\n",dirname);
        return;
    }

    // postupne budeme spracovavat vsetky adresarove polozky, kym adresar
    // obsahuje este nejake polozky (teda kym nam volanie readdir vracia
    // neNULLove vysledky)
    while((dir=readdir(dp)) != NULL)
    {
        // ak sme narazili neplatna adresarova polozka (napriklad vymazany
        // subor) budeme ju ignorovat
// toto nie je potrebne
// ked sa polozky adresara citaju pomocou funkcie readdir, tato situacia
// nemoze nastat
//        if(dir->d_fileno == 0)
//            continue;
        
        // rovnako preskocime odkazy na aktualny adresar a rodicovsky adresar
        // (hardlinky "." a "..", ktore obsahuje kazdy adresar rodiny UNIXovych
        // systemov suborov
        if(!strcmp(dir->d_name,".") ||
           !strcmp(dir->d_name,".."))
            continue;
        
        // dalej si poskladame cele meno suboru ...
        // odlozime si meno adresara do pomocneho statickeho buffera path
        strcpy(path,dirname);
        // ak na konci neobsahuje lomitko, pridame ho tam
        if(dirname[strlen(dirname)-1] != '/')
            strcat(path,"/");
        // (btw. kedze prva cast skladania cesty - predchadzajuce dva kroky -
        // su rovnake pri spracovavani vsetkych suborov, dala by sa vykonat
        // mimo cyklu, cim by sa spracovanie programu mozno zase trochu
        // urychlilo.
        // Najefektivnejsim sposobom - pri rekurzivnom prehladavani adresarovej
        // struktury - je pouzitie jedneho globalneho buffera, kde sa pridavaju
        // resp. uberaju mena suborov podla toho, ci sa vnarame hlbsie alebo
        // sa vraciame spet. Museli by sme si na kazdej urovni vnorenia
        // zapametat, kde sa konci cesta k obsahujucemu adresaru a kde sa 
        // zacina meno suboru. Vyzaduje si to trochu vecsiu programatorsku
        // zrucnost ...)
        // k takto upravenemu menu adresara pripojime meno suboru z jeho
        // adresarovej polozky
        strcat(path,dir->d_name);
        
        // a zistime si typ suboru a pristupove prava suboru
        if(lstat(path,&filestat) != 0)
        {
	        fprintf(stderr,"Error: '%s': chyba pri lstat\n",dirname);
        	continue;
        }
        
        // podla mojho nazoru nasledujuce riadky by mali byt pokusom
        // o testovanie pristupovych prav (na citanie). Testovanie pristupovych
        // prav je zlozitejsi problem, ktory sa riadi komplexnejsimi pravidlami
        // (podla toho, ci sme vlastnikom suboru, inak ak patrime do rovnakej
        // skupiny ako ma subor nastaveny, inak ako ostatni pouzivatelia.
        // Navyse treba rozlisovat minimalne efektivne a skutocne ID pouzivatela
        // a skupiny.) Na zistenie pristupovych prav sa da pouzit aj napriklad
        // volanie open (pokusime sa priamo otvorit subor s pozadovanymi pravami,
        // ak prava nename, nepodari sa nam subor otvorit - open vrati NULL).
        // Takto sa ale neda overit pravo na vykonanie, celkovo tento pristup
        // nie je prilis pekny. Inou moznostou je vyuzit volanie access, ktore
        // pouziva jadro na otestovanie pristupu k suborom. Ma dva parametre -
        // meno suboru a typ testovaneho pristupu. Ak je volanie uspesne, vrati
        // hodnotu 0, inak hodnotu -1 ...
        if(!(S_IRUSR & (filestat.st_mode & S_IRWXU)))
        {
            fprintf(stderr,"Error: nemozem citat subor %s\n",dir->d_name);
            continue;
        }
    
        // Ak sa jedna o adresar, vykoname rekurzivne jeho spracovanie (tymto
        // kodom sme prave splnili jednu z poziadaviek bonusovych casti ...)
        if(S_ISDIR(filestat.st_mode))
        {
            SearchDir(path,pattern);
            continue;
        }
        
        // Ak sa jedna o regularny subor ...
        if(!S_ISREG(filestat.st_mode))
            continue;    
        
        // ... zistime v nom pocet vyskytov patternu ...
        count = PrintCount(path,pattern);
        // a v pripade, ze je test uspesny, zobrazime najdeny pocet vyskytov
        // na standardnom vystupe (v zelanom tvare), inak chybovu spravu na 
        // chybovom vystupe ...
        if(count >= 0)        
            printf("%s > %d\n",path,count);
        else
            fprintf(stderr,"Error: %s > nemozem zistit pocet vyskytov. \n",path);
    }
}

//*****************************************************************************
// spocitanie vyskytu pattern-u v plain subore filername. Kladna alebo nulova
// navratova hodnota funkcie znamena jej uspesne vykonanie, zaporna hodnota
// indikuje chybu pocas vykonavania.
// Na tejto urovni sa budeme zaoberat spustanim detskych procesov,
// presmerovavanim standardneho vstupu na vystup, vzajomnou komunikaciou
// medzi procesmi ...
int PrintCount(char *filename,char *pattern)
{
    // zadanie vyzaduje, aby sme na zistenie poctu vyskytov patternu vytvorili
    // novy proces, v ktorom spustime prikaz grep. Aby sme ziskali vysledok
    // spracovania prikazu grep, prepojime jeho vystup pomocou datovodu s
    // rodicovskym procesom, odkial hodnotu precitame. Zadefinujeme si teda
    // premennu obsahucu deskriptory pre datovod ...
    int pipedes[2];
    // ... dalej premennu na pocet vyskytov patternu ...
    int count;
    // ... a buffer (docasnu vyrovnavajucu pamet na spracovanie vstupov)
    // na spracovanie vystupu z programu grep
    char number[NUMBER_SIZE+1];
    
    // zatial sme nezistili ziadny vyskyt patternu ...
    count = -1;
    // vytvorime spominany datovod. Vstupom pre volanie pipe je pole dvoch
    // deskriptorov, (deskriptor s indexom 0 je vystupny a s indexom 1 vstupny
    // Ak volanie uspeje, funkcia vrati 0, inak vracia -1
    if(pipe(pipedes))
    {
        fprintf(stderr,"Error: volanie pipe zlyhalo");
        exit(1);
    }
    
    // vytvorime detsky proces. Na to sluzi volanie jadra fork. Ak nie je
    // uspesne, funkcia vrati -1. V opacnom pripade vracia v detskom procese
    // hodnotu 0 a v rodicovskom procese ID dietata. Neuspech volania
    // je oznameny samozrejme len v rodicovi (dieta ani nevznikne :)
    switch(fork())
    {
        case -1 : 
            // ak fork zlyhal, skoncime (viac sa v danom momente neda urbit)
            fprintf(stderr,"Error: chyba pri fork");
            return -2;
        case 0 :            
            // dcersky proces
            // pred tym, nez spustime prikaz prikaz grep, musime presmerovat
            // do datovodu standardny vystup dietata. Momentalne ma detsky
            // proces vytvorene kopie vsetkych deskriptorov (teda aj kopie
            // oboch deskriptorov datovodu). Vystup datovodu v detskom procese
            // citat nebudeme - to bude robit rdicovsky proces, takze ho
            // zavrieme...
            close(pipedes[0]);
            // ... dalej zavrieme standardny vystup dietata. Tak sa v tabulke
            // deskriptorov vytvori miesto, do ktoreho nasledne zduplikujeme
            // vstup datovodu ...
            close(1);
            dup(pipedes[1]);
            // ... takymto sposobom sme prepojili standardny vystup dietata na
            // vstup datovodu. Vstup datovodu nam staci mat v tabulke
            // deskriptorov procesu otvoreny len raz, ten nepotrebny teda
            // zavrieme ...
            close(pipedes[1]);
            
            // ... odfiltrujeme chybove spravy (robi sa to tu jednoduchsie ako
            // v shelli ... :)
            fclose(stderr);
            // ... a spustime program grep. Volanie exec ma niekolko tvarov
            // (presnejsie 6: execl, ecexv, execle, execve, execlp a execvp). 
            // Prvym parametrom kazdeho z tvarov je cesta k vykonatelnemu
            // suboru. Ak je zadane iba meno suboru, subor sa hlada v
            // adresaroch uvedenych ako hodnota premennej prostredia PATH.
            // Druhym parametrom volania exec je zoznam parametrov v tvare,
            // aky specifikuje pismeno za slovom exec v nazve funkcie. Pismeno
            // 'l' (funkcie execl, execle a execlp) oznacuje, ze sa argumenty
            // zadavaju porade ako argumenty volania. Funkcie maju teda
            // premenlivy pocet argumentov. Argument s indexom 0 obsahuje nazov
            // procesu a moze byt iny, nez meno spustitelneho suboru. Pismeno
            // 'v' oznacuje ze druhym parametrom funkcie je pole argumentov
            // programu (tak, ako parameter argv funkcie main). Pismeno 'e' na
            // konci mena funkcie vyjadruje, ze sa pre spusteny program
            // zachovaju premenne prostredia, a pismeno 'p', ze v pripade,
            // ze je vykonatelnym programom shellovy skript, spusti sa shell,
            // ktory skript interpretuje. Zoznam argumentov musi byt ukonceny
            // hodnotou NULL
            execlp("grep","grep","-c",pattern,filename,0);
            // ak bolo volanie exec uspesne, obraz detskeho procesu je
            // kompletne nahradeny obrazom vytvorenym z programu grep, ktory
            // spustame. Uspesne volanie exec sa sem nikdy nedostane, iba ak
            // nastala chyba ...
            
            // vzhladom na to, ze sme si pred dvoma prikazom exec zavreli
            // standardny chybovy vystup, nebude nasledujuce volanie velmi
            // ucinne. Korektne by sme si mali zduplikovat chybovy vystup
            // a az tak zavriet deskriptor 2, aby sme na chybovy vystup
            // nestratili odkaz
            fprintf(stderr,"Error: spustanie grep");
            return -3;
            
        default:
            // rodicovsky proces
            // v rodicovskom procese budeme z datovodu iba citat. Vstup
            // datovodu teda zavrieme ...
            close(pipedes[1]);
            // Inicializujeme si vyrovnavaciu pamet na vysledok a precitame
            // ho z vystupu datovodu, ktory po spracovani uz nepotrebujeme ...
            memset(number,0,NUMBER_SIZE);
            read(pipedes[0],number,NUMBER_SIZE-1);
            close(pipedes[0]);
            // na zaver treba skonvertovat precitany retazec na cislo. Zase
            // kvuoli rychlosti programu sa viac oplati pre taketo jednoduche
            // transformacie pouzivat konverzne funkcie ato?, v nasom pripade
            // atoi. Ale aj uvedene riesenie je spravne ... 
            sscanf(number,"%d",&count);
    }
    // a este pockame kym skonci potomok
    // jeho stav nas ale nezaujima, preto ako parameter staci NULL
    wait(NULL);
    
    return count;
}
