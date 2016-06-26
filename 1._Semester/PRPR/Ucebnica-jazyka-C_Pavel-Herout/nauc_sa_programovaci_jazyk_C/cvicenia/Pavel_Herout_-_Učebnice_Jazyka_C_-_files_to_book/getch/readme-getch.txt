`                                       4.10. 1998  V�clav Bro��k
  Modul getch verze 1.0                Public domain
  ---------------------

#include "getch.h"

Modul emuluje t�i funkce z Borland C hlavi�kov�ho souboru <conio.h>.
V�echny m�n� nastaven� termin�lu a p�ed n�vratem je vracej� do stavu
p�e�ten�ho v inicializa�n� funkci. Tedy mimo tyto funkce si termin�l
zachov�v� obvykl� nastaven� a m��ete jej norm�ln� pou��vat (stdin, stdout).
Funkci modulu na konkr�tn�m po��ta�i m��ete otestovat p�ilo�en�m progr�mkem
test-getch.c.

* int kbhit(void)
    - Testuje stisk jak�koliv kl�vesy. Pokud je sti�t�na, vrac� ASCII k�d,
      jinak vrac� 0. K�d pozd�ji m��ete znovu p�e��st funkc� getch() nebo
      getche(). Nov�m vol�n�m kbhit() je k�d zapomenut.
      Pokud nen� stisknuta ��dn� kl�vesa, je funkce kbhit() velmi pomal�
      (b�� asi 10 ms), m��ete ji v�ak zrychlit p�edefinov�n�m hodnoty
      GETCH_USLEEP v getch.h. Pokud funkce kbhit() nefunguje, m��ete zkusit
      oddefinovat GETCH_USE_SELECT, potom se ale v�razn� zpomal� (100 ms).
* int getch(void)
    - Jako kbhit(), ale �ek� na stisk kl�vesy a k�d je zapomenut ihned.
* int getche(void)
    - Jako getch(), ale znak se z�rove� vyp�e na termin�l.


P�ed prvn�m pou�it�m mus�te modul inicializovat.

* int getch_init(int sigcatch)
    - Otev�e soubor /dev/tty a ulo�� sou�asn� nastaven� termin�lu. Pokud m�
      parametr sigcatch hodnotu GETCH_SIGINT, zaregistruje se ovlada� sign�lu
      SIGINT, kter� provede �klid a vyvol�n� default akce SIGINT. Funkce d�le
      otestuje mo�nost zm�ny parametr� termin�lu. V p��pad� �sp�chu vrac� 0,
      p�i ne�sp�chu -1.


Pokud ji� nepot�ebujete funkce modulu, zavolejte �klid.

* void getch_end(void)
    - Zav�e soubor /dev/tty a p��padn� nastav� default ovlada� pro SIGINT.


M��ete pou��t hotov� ovlada� pro sign�ly ukon�uj�c� b�h programu.

* void getch_sigcatch(int sig)

