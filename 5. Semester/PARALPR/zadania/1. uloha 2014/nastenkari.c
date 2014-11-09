/*
Meno:
Datum:

Simulujte nasledujucu situaciu. Dvaja nastenkari menia raz za cas nastenku. Menenie nastenky trva nejaky cas (v simulacii 3s) a potom si idu pripravovat dalsiu zmenu nastenky (v simulacii 5s). Desiati zamestnanci si chodia pozerat nastenku, pricom pozeranie im trva nejaky cas (v simulacii 1s) a potom idu trosku popracovat (v simulacii 2s). Cela simulacia nech trva 30s.

1. Doplnte do programu premennu pocitajucu zmeny nastenky, po skonceni simulacie vypiste jej hodnotu. [2b]

2. Zabezpecte, aby iba jeden nastenkar mohol menit nastenku a to len vtedy, ked si ziaden zamestnanec nepozera nastenku. Zamestnanci si mozu naraz pozerat nastenku viaceri. [5b]

3. Osetrite v programe spravne ukoncenie simulacie po uplynuti stanoveneho casu tak, aby nastenkar ani zamestnanec po stanovenom case uz ziadnu cinnost nezacal. [3b]

Poznamky:
- na synchronizaciu pouzite iba mutexy+podmienene premenne alebo semafory
- nespoliehajte sa na uvedene casy, simulacia by mala fungovat aj s inymi casmi alebo s nahodne generovanymi casmi
- build (console): gcc nastenkari.c -o nastenkari -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// signal na zastavenie simulacie
int stoj = 0;

// nastenkar
void nastenkar_men(void) {
    sleep(3);
}

void nastenkar_pripravuj(void) {
    sleep(5);
}

void *nastenkar(void *ptr) {
    
    while(!stoj) {
        nastenkar_men();
        nastenkar_pripravuj();
    }
    return NULL;
}

// zamestnanec
void zamestnanec_citaj(void) {
    sleep(1);
}

void zamestnanec_pracuj(void) {
    sleep(2);
}

void *zamestnanec(void *ptr) {
    
    while(!stoj) {
        zamestnanec_citaj();
        zamestnanec_pracuj();
    }
    return NULL;
}

// main f.
int main(void) {
    int i;

    pthread_t nastenkari[2];
    pthread_t zamestnanci[10];

    for (i=0;i<2;i++) pthread_create(&nastenkari[i], NULL, &nastenkar, NULL);
    for (i=0;i<10;i++) pthread_create(&zamestnanci[i], NULL, &zamestnanec, NULL);

    sleep(30);
    stoj = 1;

    for (i=0;i<2;i++) pthread_join(nastenkari[i], NULL);
    for (i=0;i<10;i++) pthread_join(zamestnanci[i], NULL);

    exit(EXIT_SUCCESS);
}
