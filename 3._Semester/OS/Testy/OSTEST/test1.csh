Prikazy (kod), ktorymi ste danu ulohu vyriesili, uvedte medzi riadky
RIESENIE_ZACIATOK a RIESENIE_KONIEC prislusneho prikladu. Vysledok uvedte
na riadok za slovo VYSLEDOK, pricom za slovom VYSLEDOK nechajte jednu
medzeru.

Ked mate prehladavat adresar, vzdy ho prehladavajte do hlbky (pokial nie je
v konkretnom zadani uvedene inak).

Za slovo SHELL uvedte shell, ktory ste pouzili na riesenie uloh
SHELL csh

======================================================================
PRIKLAD 1

Kolko obycajnych suborov v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2
ma menej ako 100 riadkov?

VYSLEDOK 


RIESENIE_ZACIATOK
find /home/OS/predtest -type f -exec wc -l {} \; | tr -s " " | cut -d " " -f 2 | grep -c "\<..\>"
RIESENIE_KONIEC
======================================================================
PRIKLAD 2

Kolko symbolickych liniek v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2
ma cielovu cestu dlhsiu ako 10 bajtov?

VYSLEDOK 

RIESENIE_ZACIATOK
find /home/OS/predtest -type l -size +10c | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 3

Kolko netextovych (obycajnych) suborov sa nachadza v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2

VYSLEDOK 
find /home/OS/predtest -type f -exec file {} \; | grep -vc "/<text/>"
RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 4

Kolko obycajnych suborov sa nachadza v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2

VYSLEDOK 

RIESENIE_ZACIATOK
find /home/OS/predtest -f | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 5

Kolko prazdnych podadresarov obsahuje adresar
/home/OS/pocitacove/testovaci_adresar/z/test2

VYSLEDOK 

RIESENIE_ZACIATOK
find /home/OS/predtest -type d -empty | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 6

Aka je velkost najmensieho adresara v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2
Velkost urcte v bajtoch.

VYSLEDOK 

RIESENIE_ZACIATOK
find /home/OS/predtest -type d -printf "%s\n" | sort -n | uniq -c
RIESENIE_KONIEC
======================================================================
PRIKLAD 7

Kolko podadresarov adresara
/home/OS/pocitacove/testovaci_adresar/z/test2
obsahuje viac ako 3 obycajnych suborov?
V konkretnom podadresari pracujte len so subormi, ktore su priamo v nom.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 8

V kolkych podadresaroch adresara
/home/OS/pocitacove/testovaci_adresar/z/test2
maju obycajne subory spolu viac ako 1000 bajtov?
V konkretnom podadresari pracujte len so subormi, ktore su priamo v nom.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 9

Kolko podadresarov adresara
/home/OS/pocitacove/testovaci_adresar/z/test2
je v hlbke viac ako 2 urovni ?
Hlbka znamena pocet adresarov na ceste medzi zadanym adresarom
a spracovavanym adresarom.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 10

Aka je velkost najmensieho obycajneho suboru v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2
Velkost urcte v slovach.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 11

Kolko riadkov v subore
/home/OS/predtest/vstupy/ccero10.txt
ma viac ako 100 znakov?

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 12

Kolko riadkov v subore
/home/OS/predtest/vstupy/lostw10.txt
ma menej ako 20 znakov?

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 13

Kolko riadkov v subore
/home/OS/predtest/vstupy/advsh12.txt
ma viac ako 20 slov?

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 14

Kolko slov by sa zmenilo v subore
/home/OS/predtest/vstupy/advsh12.txt
keby sme v nom skonvertovali vsetky velke pismena na male?
Slovo je postupnost znakov oddelena jednou alebo viacerymi medzerami.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 15

Kolko slov by sa zmenilo v subore
/home/OS/predtest/vstupy/ccero10.txt
keby sme v nom skonvertovali vsetky male pismena na velke?
Slovo je suvisla postupnost pismen.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 16

Kolko slov by sa zmenilo v subore
/home/OS/predtest/vstupy/bskrv11.txt
keby sme v nom skonvertovali vsetky velke pismena na male?
Slovo je suvisla postupnost pismen.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 17

Kolko slov by sa zmenilo v subore
/home/OS/predtest/vstupy/advsh12.txt
keby sme v nom zrusili vsetky pomlcky a podciarkovniky?
Slovo je postupnost znakov oddelena jednou alebo viacerymi medzerami.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 18

Kolko slov by sa zmenilo v subore
/home/OS/predtest/vstupy/bskrv11.txt
keby sme v nom zrusili vsetky cislice?
Slovo je postupnost znakov oddelena jednou alebo viacerymi medzerami.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 19

Kolko riadkov v subore
/home/OS/predtest/vstupy/bskrv11.txt
ma viac ako 20 znakov?

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 20

Kolko riadkov v subore
/home/OS/predtest/vstupy/bskrv11.txt
ma menej ako 20 slov?

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 21

Kolko sekund bol pouzivatel root celkovo prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Apr
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 22

Kolko sekund bol pouzivatel prochazk celkovo prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Apr
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 23

Kolko krat bol pouzivatel lehockym prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Feb
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 24

Kolko krat bol pouzivatel root prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Feb
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 25

Kolko pouzivatelov je prave prihlasenych?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/utmp.2

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 26

Kolko pouzivatelov je prave prihlasenych viac krat?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/utmp.3

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 27

Kolko sekund bol pouzivatel prochazk celkovo prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Feb
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 28

Kolko sekund bol pouzivatel steinmul celkovo prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Feb
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 29

Kolko syntaktickych chyb je v skripte
/home/OS/pocitacove/csh/riesene_ulohy/lacko_12.csh

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
======================================================================
PRIKLAD 30

Kolko roznych programov moze byt spustenych pocas behu skriptu
/home/OS/pocitacove/csh/riesene_ulohy/lacko_12.csh

VYSLEDOK 

RIESENIE_ZACIATOK
RIESENIE_KONIEC
