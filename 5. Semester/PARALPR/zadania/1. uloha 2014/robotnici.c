/*
Meno:
Datum:

Simulujte nasledujcu situaciu. Dvadsat robotnikov pracuje na stavbe. Kazdy robotnik nejaky cas pracuje (v simulacii 3s) a potom sa obcerstvuje v pohostinstve, kde si da jedno pivo (v simulacii 5s). 

1. Doplnte do programu premennu pocitajucu celkovy pocet vypitych piv. [2b]

2. Simulujte situacu, ze do pohostinstva sa zmesti iba desať robotnikov, ti co chcu pit a nezmestia sa, musia pockat pred pohostinstvom. [4b]

3. Zabezpecte, aby sa robotnici po obcerstveni vsetci pockali a az potom zacali pracovat. [4b]

Poznamky:
- na synchronizaciu pouzite iba mutexy+podmienene premenne alebo semafory
- nespoliehajte sa na uvedene casy, simulacia by mala fungovat aj s inymi casmi alebo s nahodne generovanymi casmi
- build (console): gcc robotnici.c -o robotnici -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// signal na zastavenie simulacie
int stoj = 0;

//  robotnik
void robotnik_pracuj(void) {
    sleep(3);
}

void robotnik_pi(void) {
    sleep(5);
}

void *robotnik(void *ptr) {
    
    while(!stoj) {
        robotnik_pracuj();
        robotnik_pi();
    }
    return NULL;
}

// main f.
int main(void) {
    int i;

    pthread_t robotnici[30];

    for (i=0;i<30;i++) pthread_create(&robotnici[i], NULL, &robotnik, NULL);

    sleep(30);
    stoj = 1;

    for (i=0;i<30;i++) pthread_join(robotnici[i], NULL);

    exit(EXIT_SUCCESS);
}
