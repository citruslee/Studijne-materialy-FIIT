Autor: Michal Samiec 
Vysledky su kontrolovane na predteste a vsetky su dobre, horsie je o 
so sposobom ich zistenia, co som vedel to som vypotil

Prikazy (kod), ktorymi ste danu ulohu vyriesili, uvedte medzi riadky
RIESENIE_ZACIATOK a RIESENIE_KONIEC prislusneho prikladu. Vysledok uvedte
na riadok za slovo VYSLEDOK, pricom za slovom VYSLEDOK nechajte jednu
medzeru.

Ked mate prehladavat adresar, vzdy ho prehladavajte do hlbky (pokial nie je
v konkretnom zadani uvedene inak).

Za slovo SHELL uvedte shell, ktory ste pouzili na riesenie uloh
csh 

======================================================================
PRIKLAD 1

Kolko obycajnych suborov v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2
ma menej ako 100 riadkov?

VYSLEDOK 149

RIESENIE_ZACIATOK
wc -l `find /home/OS/pocitacove/testovaci_adresar/z/test2 -type f ` | awk '$1<100' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 2

Kolko symbolickych liniek v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2
ma cielovu cestu dlhsiu ako 10 bajtov?

VYSLEDOK 11

RIESENIE_ZACIATOK
find /home/OS/pocitacove/testovaci_adresar/z/test2/ -type l -printf %s"\n" | awk '$1>10' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 3

Kolko netextovych (obycajnych) suborov sa nachadza v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2

VYSLEDOK 58

RIESENIE_ZACIATOK
file `find /home/OS/pocitacove/testovaci_adresar/z/test2 -type f` | grep -v -w 'text$' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 4

Kolko obycajnych suborov sa nachadza v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2

VYSLEDOK 149

RIESENIE_ZACIATOK
find /home/OS/pocitacove/testovaci_adresar/z/test2 -type f | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 5

Kolko prazdnych podadresarov obsahuje adresar
/home/OS/pocitacove/testovaci_adresar/z/test2

VYSLEDOK 10

RIESENIE_ZACIATOK
find /home/OS/pocitacove/testovaci_adresar/z/test2 -type d -empty | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 6

Aka je velkost najmensieho adresara v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2
Velkost urcte v bajtoch.

VYSLEDOK 1

RIESENIE_ZACIATOK
du -d0 `find /home/OS/pocitacove/testovaci_adresar/z/test2/ -type d` | awk '{print $1}' | sort | head -1

 alebo toto , podla toho ako to mysleli ti, ktori to vymyslali

du `find /home/OS/pocitacove/testovaci_adresar/z/test2/ -type d -maxdepth 1 -mindepth 1` |  | sort | head -1
RIESENIE_KONIEC
======================================================================
PRIKLAD 7

Kolko podadresarov adresara
/home/OS/pocitacove/testovaci_adresar/z/test2
obsahuje viac ako 3 obycajnych suborov?
V konkretnom podadresari pracujte len so subormi, ktore su priamo v nom.

VYSLEDOK 22

RIESENIE_ZACIATOK
find /home/OS/pocitacove/testovaci_adresar/z/test2/ -type f -printf "%h\n" | sort | uniq -c | awk '($1 > 3)' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 8

V kolkych podadresaroch adresara
/home/OS/pocitacove/testovaci_adresar/z/test2
maju obycajne subory spolu viac ako 1000 bajtov?
V konkretnom podadresari pracujte len so subormi, ktore su priamo v nom.

VYSLEDOK 34

RIESENIE_ZACIATOK
#!/bin/csh
# Pocet poadresarov v adresari, v ktorych maju obycajne subory spolu viac ako 1000 bajtov
set zoznam = (`find /home/OS/pocitacove/testovaci_adresar/z/test2 -type d`)
@ adr = 0;
foreach a (te/te$zoznam:q)
    @ b = `find $a -type f -maxdepth 1 -exec wc -c {} \; | awk '{a=a+$1} END {print a}'`;
    if ($b > 1000) @ adr++;
end;
echo $adr;
RIESENIE_KONIEC
======================================================================
PRIKLAD 9

Kolko podadresarov adresara
/home/OS/pocitacove/testovaci_adresar/z/test2
je v hlbke viac ako 2 urovni ?
Hlbka znamena pocet adresarov na ceste medzi zadanym adresarom
a spracovavanym adresarom.

VYSLEDOK 11

RIESENIE_ZACIATOK
find /home/OS/pocitacove/testovaci_adresar/z/test2/ -type d -mindepth 4 | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 10

Aka je velkost najmensieho obycajneho suboru v adresari
/home/OS/pocitacove/testovaci_adresar/z/test2
Velkost urcte v slovach.

VYSLEDOK 0

RIESENIE_ZACIATOK
wc -w `find /home/OS/pocitacove/testovaci_adresar/z/test2/ -type f` | sort | awk '{print $1}' | head -n 1
RIESENIE_KONIEC
======================================================================
PRIKLAD 11

Kolko riadkov v subore
/home/OS/predtest/vstupy/ccero10.txt
ma viac ako 100 znakov?

VYSLEDOK 0

RIESENIE_ZACIATOK
 cat /home/OS/predtest/vstupy/lostw10.txt | awk 'length($0)>100' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 12

Kolko riadkov v subore
/home/OS/predtest/vstupy/lostw10.txt
ma menej ako 20 znakov?

VYSLEDOK 1526

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy/lostw10.txt | awk 'length($0)<20' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 13

Kolko riadkov v subore
/home/OS/predtest/vstupy/advsh12.txt
ma viac ako 20 slov?

VYSLEDOK 0

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy/lostw10.txt | awk 'NF>20' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 14

Kolko slov by sa zmenilo v subore
/home/OS/predtest/vstupy/advsh12.txt
keby sme v nom skonvertovali vsetky velke pismena na male?
Slovo je postupnost znakov oddelena jednou alebo viacerymi medzerami.

VYSLEDOK 12859

RIESENIE_ZACIATOK
 cat /home/OS/predtest/vstupy/advsh12.txt | tr ' ' '\n' | grep '[[:upper:]]' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 15

Kolko slov by sa zmenilo v subore
/home/OS/predtest/vstupy/ccero10.txt
keby sme v nom skonvertovali vsetky male pismena na velke?
Slovo je suvisla postupnost pismen.

VYSLEDOK 14539

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy/ccero10.txt | tr -c '[[:alpha:]]' '\n' | grep '[[:lower:]]' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 16

Kolko slov by sa zmenilo v subore
/home/OS/predtest/vstupy/bskrv11.txt
keby sme v nom skonvertovali vsetky velke pismena na male?
Slovo je suvisla postupnost pismen.

VYSLEDOK 7476

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy/bskrv11.txt | tr -c '[[:alpha:]]' '\n' | grep '[[:upper:]]' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 17

Kolko slov by sa zmenilo v subore
/home/OS/predtest/vstupy/advsh12.txt
keby sme v nom zrusili vsetky pomlcky a podciarkovniky?
Slovo je postupnost znakov oddelena jednou alebo viacerymi medzerami.

VYSLEDOK 941

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy/advsh12.txt | tr ' ' '\n' | grep '[-_]' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 18

Kolko slov by sa zmenilo v subore
/home/OS/predtest/vstupy/bskrv11.txt
keby sme v nom zrusili vsetky cislice?
Slovo je postupnost znakov oddelena jednou alebo viacerymi medzerami.

VYSLEDOK 82

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy/bskrv11.txt | tr ' ' '\n' | grep '[[:digit:]]' | wc -l
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

VYSLEDOK 5525

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy/bskrv11.txt | awk 'length($0)>20' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 21

Kolko sekund bol pouzivatel root celkovo prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Apr
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 0

RIESENIE_ZACIATOK
last -f /home/OS/predtest/vstupy/wtmp.02Apr | grep '^root' | grep -v 'still' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 22

Kolko sekund bol pouzivatel prochazk celkovo prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Apr
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 2854

RIESENIE_ZACIATOK
last -s -f /home/OS/predtest/vstupy/wtmp.02Apr | grep 'prochazk' | grep -v 'still' | awk '{print $11}' | tr ')' ' ' | awk '{a=a+$1}END{print a}'
RIESENIE_KONIEC
======================================================================
PRIKLAD 23

Kolko krat bol pouzivatel lehockym prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Feb
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 3

RIESENIE_ZACIATOK
last -f /home/OS/predtest/vstupy/wtmp.02Feb | grep '^lehockym' | grep -v 'still' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 24

Kolko krat bol pouzivatel root prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Feb
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 0

RIESENIE_ZACIATOK
last -f /home/OS/predtest/vstupy/wtmp.02Feb | grep '^root' | grep -v 'still' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 25

Kolko pouzivatelov je prave prihlasenych?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/utmp.2

VYSLEDOK 63 alebo 30

RIESENIE_ZACIATOK
last -f /home/OS/predtest/vstupy/utmp.2 | grep 'still' | wc -l

		alebo (ktovie ako to zas myslel ten kto tot vymyslal)

last -f /home/OS/predtest/vstupy/utmp.2 | grep 'still' | awk '{print $1}' | sort | uniq | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 26

Kolko pouzivatelov je prave prihlasenych viac krat?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/utmp.3

VYSLEDOK 16

RIESENIE_ZACIATOK
last -f /home/OS/predtest/vstupy/utmp.3 | grep 'in$' | awk '{print $1}' | sort | uniq -c | awk '$1>1' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 27

Kolko sekund bol pouzivatel prochazk celkovo prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Feb
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 13217

RIESENIE_ZACIATOK
last -s -f /home/OS/predtest/vstupy/wtmp.02Feb | grep '^prochazk' | awk -F "(" '{print $2}' | tr ')' ' ' | awk '{a=a+$1} END {print a}'
RIESENIE_KONIEC
======================================================================
PRIKLAD 28

Kolko sekund bol pouzivatel steinmul celkovo prihlaseny v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy/wtmp.02Feb
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 1054115

RIESENIE_ZACIATOK
last -s -f /home/OS/predtest/vstupy/wtmp.02Feb | grep '^steinmul' | awk -F "(" '{print $2}' | tr ')' ' ' | awk '{a=a+$1} END {print a}'
RIESENIE_KONIEC
======================================================================
PRIKLAD 29

Kolko syntaktickych chyb je v skripte
/home/OS/pocitacove/csh/riesene_ulohy/lacko_12.csh

VYSLEDOK 0

RIESENIE_ZACIATOK
csh -n /home/OS/pocitacove/csh/riesene_ulohy/lacko_12.csh
RIESENIE_KONIEC
======================================================================
PRIKLAD 30

Kolko roznych programov moze byt spustenych pocas behu skriptu
/home/OS/pocitacove/csh/riesene_ulohy/lacko_12.csh

VYSLEDOK 6

RIESENIE_ZACIATOK
som to rucne spocital
RIESENIE_KONIEC
