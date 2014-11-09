/*
Meno:
Datum:

Simulujte nasledujucu situaciu. Styria murari omietaju miestnosti, pracuju po dvojiciach. Vzdy dvaja murari nahadzuju omietky (v simulacii 2s) a sucane druhi dvaja ich zarovnavaju (v simulacii 3s); a potom sa dvojice vymenia, a prvi dvaja zarovnavaju (3s) a druhi dvaja nahadzuju (2s). Cela simulacia nech trva 30s.

1. Doplnte do programu vypis na obrazovku v ktorom bude cislo robotnika 1 az N, cinnost, a ci cinnost zacina alebo konci, napr. "robotnik c.2 hadz zaciatok". Nakoniec do programu doplnte vypis, kolko vypisov na brazovku bolo vykonanych. [3b]

2. Zabezpecte, aby sa dvojice murarov spravne striedali (a zacali so spravnou cinnostou), cize naraz zacinaju dvaja nahadzovat a zaroven dvaja zarovnavat, potom sa pockaju a vystriedaju. [4b]

3. Osetrite v programe spravne ukoncenie simulacie po uplynuti stanoveneho casu tak, aby murar po stanovenom case uz nezacal dalsiu cinnost. [2b]

Poznamky:
- na synchronizaciu pouzite iba mutexy+podmienene premenne alebo semafory
- nespoliehajte sa na uvedene casy, simulacia by mala fungovat aj s inymi casmi
- build (console): gcc murari.c -o murari -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// signal na zastavenie simulacie
int stoj = 0;

// murar
void hadz(void) {
    sleep(2);
}

void zarovnavaj(void) {
    sleep(3);
}

void *murar(void *ptr) {

    while(!stoj) {
        hadz();
        zarovnavaj();
    }
    return NULL;
}

int main(void) {
    int i;

    pthread_t murari[4];

    for (i=0;i<4;i++) pthread_create(&murari[i], NULL, &murar, NULL);

    sleep(30);
    stoj = 1;

    for (i=0;i<4;i++) pthread_join(murari[i], NULL);

    exit(EXIT_SUCCESS);
}