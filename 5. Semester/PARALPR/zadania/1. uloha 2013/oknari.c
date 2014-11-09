/*
Meno:
Datum:

Simulujte nasledujucu situaciu. Piati oknari osadzaju okna. Na osadenie maleho okna su potrebni dvaja oknari a osadzaju ho nejaky cas (v simulacii 2s) a na osadenie velkeho okna su potrebni 3 oknari a osadzaju ho dlhsi cas (v simulacii 3s). Okna su naskadane v kamione v takomto poradi (V - velke 15x, M - male 15x): "VMMVVMMMVVVVVMMMVVVVMMMVVVMMMM". Simulacia konci, ked su vsetky okna osadene.

1. Doplnte do programu vypis na obrazovku v ktorom bude cislo robotnika 1 az N, cinnost, a ci cinnost zacina alebo konci, napr. "robotnik c.2 osad_male zaciatok". Doplnte do programu pocitadla pre male a velke okna, vzdy ked je okno osadene, inkrementujte zodpovedajuce pocitadlo. [3b]

2. Zabezpecte, aby podla velkosti spravny pocet oknarov osadzal okno spravny cas, ak je to potrebne, musia na seba pockat. [5b]

3. Osetrite v programe spravne ukoncenie simulacie po osadeni vetkych okien. [2b]

Poznamky:
- na synchronizaciu pouzite iba mutexy+podmienene premenne alebo semafory
- nespoliehajte sa na uvedene casy, simulacia by mala fungovat aj s inymi casmi
- build (console): gcc oknari.c -o oknari -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// okna
char* okna = "VMMVVMMMVVVVVMMMVVVVMMMVVVMMMM";

// signal na zastavenie simulacie
int stoj = 0;

// oknar
void osad_male(void) {
    sleep(2);
}

void osad_velke(void) {
    sleep(3);
}

void *oknar(void *ptr) {

    while(!stoj) {
        male();
        velke();
    }
    return NULL;
}

int main(void) {
    int i;

    pthread_t oknari[5];

    for (i=0;i<5;i++) pthread_create(&oknari[i], NULL, &oknar, NULL);

   // zmenit, simulacia koci ked su okna osadene
    sleep(30);
    stoj = 1;

    for (i=0;i<5;i++) pthread_join(oknari[i], NULL);

    exit(EXIT_SUCCESS);
}