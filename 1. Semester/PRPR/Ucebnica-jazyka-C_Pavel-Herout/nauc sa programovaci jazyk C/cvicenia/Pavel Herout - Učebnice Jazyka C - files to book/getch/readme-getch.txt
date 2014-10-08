`                                       4.10. 1998  Václav Brožík
  Modul getch verze 1.0                Public domain
  ---------------------

#include "getch.h"

Modul emuluje tøi funkce z Borland C hlavièkového souboru <conio.h>.
Všechny mìní nastavení terminálu a pøed návratem je vracejí do stavu
pøeèteného v inicializaèní funkci. Tedy mimo tyto funkce si terminál
zachovává obvyklé nastavení a mùžete jej normálnì používat (stdin, stdout).
Funkci modulu na konkrétním poèítaèi mùžete otestovat pøiloženým prográmkem
test-getch.c.

* int kbhit(void)
    - Testuje stisk jakékoliv klávesy. Pokud je stištìna, vrací ASCII kód,
      jinak vrací 0. Kód pozdìji mùžete znovu pøeèíst funkcí getch() nebo
      getche(). Novým voláním kbhit() je kód zapomenut.
      Pokud není stisknuta žádná klávesa, je funkce kbhit() velmi pomalá
      (bìží asi 10 ms), mùžete ji však zrychlit pøedefinováním hodnoty
      GETCH_USLEEP v getch.h. Pokud funkce kbhit() nefunguje, mùžete zkusit
      oddefinovat GETCH_USE_SELECT, potom se ale výraznì zpomalí (100 ms).
* int getch(void)
    - Jako kbhit(), ale èeká na stisk klávesy a kód je zapomenut ihned.
* int getche(void)
    - Jako getch(), ale znak se zároveò vypíše na terminál.


Pøed prvním použitím musíte modul inicializovat.

* int getch_init(int sigcatch)
    - Otevøe soubor /dev/tty a uloží souèasné nastavení terminálu. Pokud má
      parametr sigcatch hodnotu GETCH_SIGINT, zaregistruje se ovladaè signálu
      SIGINT, který provede úklid a vyvolání default akce SIGINT. Funkce dále
      otestuje možnost zmìny parametrù terminálu. V pøípadì úspìchu vrací 0,
      pøi neúspìchu -1.


Pokud již nepotøebujete funkce modulu, zavolejte úklid.

* void getch_end(void)
    - Zavøe soubor /dev/tty a pøípadnì nastaví default ovladaè pro SIGINT.


Mùžete použít hotový ovladaè pro signály ukonèující bìh programu.

* void getch_sigcatch(int sig)

