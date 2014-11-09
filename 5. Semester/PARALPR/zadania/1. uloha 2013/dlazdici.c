/*
Meno:
Datum:

Simulujte nasledujucu situaciu. Styria dlazdici kladu dlazbu a dvaja pomocnici im pripravuju dlazdice. Jeden pomocnik pravuje velke dlazdice (kazdu za nejaky cas, v simulacii 2s) a druhy pomocnik pripravuje male dlazdice (kazdu, za nejaky cas, v simulacii 1s) a davaju dlazdice na kopu, kde sa zmesti 10 dlazdic. Dlazdic velku dlazdicu kladie nejaky cas (v simulacii 3s) a malu dlazdicu tiez nejaky cas (2s), dlazdice si berie z kopy. Cela simulacia nech trva 30s.
   
1. Doplnte do programu vypis na obrazovku v ktorom bude cislo robotnika 1 az N, cinnost, a ci cinnost zacina alebo konci, napr. "robotnik c.2 uloz zaciatok". Doplnte do programu pocitadla pokladenych malych a velkych dlazdic, na konci simulaci vypiste hodnoty pocitadiel. [3b]
   
2. Zabezpecte, aby na kopu bolo ulozene maximalne 10 dlazdic a zabezpecte spravny pristup ku kope dlazdic. Kopu simulujte vhodne zvolenou udajovou strukturou. [4b]

3. Osetrite v programe spravne ukoncenie simulacie po uplynuti stanoveneho casu tak, aby murar po stanovenom case uz nezacal dalsiu cinnost. [2b]

Poznamky:
- na synchronizaciu pouzite iba mutexy+podmienene premenne alebo semafory
- nespoliehajte sa na uvedene casy, simulacia by mala fungovat aj s inymi casmi
- build (console): gcc dlazdici.c -o dlazdici -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// signal na zastavenie simulacie
int stoj = 0;

// dlazdic
void uloz(void) {
    sleep(1);
}

void *dlazdic(void *ptr) {

    while(!stoj) {
        uloz();
    }
    return NULL;
}

// pomocnik
void poloz_malu(void) {
    sleep(1);
}

void poloz_velku(void) {
    sleep(1);
}

void *pomocnik1(void *ptr) {

    while(!stoj) {
        poloz_malu();
    }
    return NULL;
}

void *pomocnik2(void *ptr) {

    while(!stoj) {
        poloz_velku();
    }
    return NULL;
}

int main(void) {
    int i;

    pthread_t robotnici[6];

    for (i=0;i<4;i++) pthread_create(&robotnici[i], NULL, &dlazdic, NULL);
   pthread_create(&robotnici[4], NULL, &pomocnik1, NULL);
   pthread_create(&robotnici[5], NULL, &pomocnik2, NULL);

    sleep(30);
    stoj = 1;

    for (i=0;i<6;i++) pthread_join(robotnici[i], NULL);

    exit(EXIT_SUCCESS);
}