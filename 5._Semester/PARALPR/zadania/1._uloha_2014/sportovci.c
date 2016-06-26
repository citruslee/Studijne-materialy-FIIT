/*
Meno:
Datum:

Simulujte nasledujcu situaciu. Dvadsat sportovcov (desat muzov a desat zien) spolu trenuju beh. Kazdy sportovec po kazdom odbehnutom okruhu si oddychne a potom zase ide na start a zase bezi. Muzovi beh trva nejaky cas (v simulacii 2s) a potom oddychuje (v simulacii 2s). Zene beh trva nejaky cas (v simulacii 3s) a potom oddychuje (v simulacii 3s). 

1. Doplnte do programu premennu pocitajucu pocet dokoncenych okruhov, ktory spolu vsetci sportovci odbehli (jedno pocitadlo pre celu skupinu). [2b]

2. Zabezpecte ukoncenie simulacie, ked kazdy muz odbehne 15 okruhov a kazda zena odbehne 10 okruhov. [2b]

3. Zabezpecte, aby sa vsetci sportovci (co budu bezat dalsi okruh) po oddychu na starte pockali a az potom vystartovali do dalsieho kola. [6b]

Poznamky:
- na synchronizaciu pouzite iba mutexy+podmienene premenne alebo semafory
- nespoliehajte sa na uvedene casy, simulacia by mala fungovat aj s inymi casmi alebo s nahodne generovanymi casmi
- build (console): gcc sportovci.c -o sportovci -lpthread
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

// signal na zastavenie simulacie
int stoj = 0;
	
void muz_bez(void) {
    sleep(2);
}

//  muz
void muz_oddychuj(void) {
    sleep(2);
}

void *muz(void *ptr) {
    
    while(!stoj) {
        muz_bez();
        muz_oddychuj();
    }
    return NULL;
}

// zena
void zena_bez(void) {
    sleep(3);
}

void zena_oddychuj(void) {
    sleep(2);
}

void *zena(void *ptr) {
    
    while(!stoj) {
        zena_bez();
        zena_oddychuj();
    }
    return NULL;
}

// main f.
int main(void) {
    int i;

    pthread_t zeny[10];
    pthread_t muzi[10];

    for (i=0;i<10;i++) pthread_create(&zeny[i], NULL, &zena, NULL);
    for (i=0;i<10;i++) pthread_create(&muzi[i], NULL, &muz, NULL);

    sleep(30);
    stoj = 1;

    for (i=0;i<10;i++) pthread_join(zeny[i], NULL);
    for (i=0;i<10;i++) pthread_join(muzi[i], NULL);

    exit(EXIT_SUCCESS);
}
