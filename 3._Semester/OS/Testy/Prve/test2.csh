Autor: Michal Samiec 

Prikazy (kod), ktorymi ste danu ulohu vyriesili, uvedte medzi riadky
RIESENIE_ZACIATOK a RIESENIE_KONIEC prislusneho prikladu. Vysledok uvedte
na riadok za slovo VYSLEDOK, pricom za slovom VYSLEDOK nechajte jednu
medzeru.

Ked mate prehladavat adresar, vzdy ho prehladavajte do hlbky a uvazujte
aj zadany adresar (pokial nie je v konkretnom zadani uvedene inak).

Ked pri hladani maxim alebo minim viacero suborov (adresarov, slov,
pismen, ...) splna podmienku, treba vypisat vsetky, zoradene podla abecedy
a oddelene jednou medzerou.

Za slovo SHELL uvedte shell, ktory ste pouzili na riesenie uloh
SHELL csh


Preriesit 5,

======================================================================
PRIKLAD 1

Kolko obycajnych suborov sa nachadza v adresari
/home/OS/predtest/vstupy-2/test2

VYSLEDOK 200

RIESENIE_ZACIATOK
find /home/OS/predtest/vstupy-2/test2 -type f | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 2

Zistite pocet slov v subore
/home/OS/predtest/vstupy-2/poe3v10.txt

VYSLEDOK 103213

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy-2/poe3v10.txt | wc -w
RIESENIE_KONIEC
======================================================================
PRIKLAD 3

Kolko znakov ma obsah premennej MANPATH ?

VYSLEDOK 44

RIESENIE_ZACIATOK
echo $MANPATH | awk '{ print length}'
RIESENIE_KONIEC
======================================================================
PRIKLAD 4

Prehladajte adresar
/home/OS/pocitacove/csh
a jeho podadresare a zistite kolko obycajnych suborov v nich
nema priponu.

VYSLEDOK 8

RIESENIE_ZACIATOK
find /home/OS/pocitacove/csh -type f ! -name "*.*" | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 5

V adresari
/home/OS/predtest/vstupy-2/test8
a jeho podadresaroch najdite textove subory, v ktorych obsahu sa vyskytuje
ich meno a uvedte ich pocet.

VYSLEDOK 84

RIESENIE_ZACIATOK
set subory = (`find /home/OS/predtest/vstupy-2/test8 -type f -print`)
set a = 0
foreach s ($subory)
       set su = $s:t
       if ( `file "$s" | awk '{print $NF}'` != "text" )  continue;
       set sub = `cat $s |  grep -F -c "$su"`
       if ( "$sub" != "0"  ) then
               @ a ++
               echo $s
       endif
end
echo $a
RIESENIE_KONIEC
======================================================================
PRIKLAD 6

Kolko skrytych obycajnych suborov sa nachadza v adresari
/home/OS/predtest/vstupy-2/test5
a jeho podadresaroch ?

VYSLEDOK 38

RIESENIE_ZACIATOK
find /home/OS/predtest/vstupy-2/test5 -type f -name '.*' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 7

Kolko adresarov, ktore nemaju ziadne podadresare, sa nachadza
v adresari
/home/OS/predtest/vstupy-2/test3
a jeho podadresaroch ?

VYSLEDOK 32

RIESENIE_ZACIATOK
ls -al `find /home/OS/predtest/vstupy-2/test3 -type d` | grep ' \.$' | awk 'length($2)<2 {if ($2==2) print $2}' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 8

V adresari
/home/OS/predtest/vstupy-2/test3
a jeho podadresaroch najdite obycajny subor, ktory bol najmenej davno modifikovany
a uvedte jeho meno.
Ak je takych suborov viac, uvedte vsetky mena usporiadane podla abecedy.

VYSLEDOK iny sub3or test

RIESENIE_ZACIATOK
#!/bin/csh
set fi = `find /home/OS/predtest/vstupy-2/test3 -type f -print `
set files = ""
foreach f ($fi)
       set file = `find /home/OS/predtest/vstupy-2/test3 -type f -newer $f`
       if ( $#file == 0 ) set files = "$files"" ""$f:t"
end
set a = `echo $files | tr " " "\n" | sort`
RIESENIE_KONIEC
======================================================================
PRIKLAD 9

Aky je sucet vsetkych cisel, ktore sa vyskytuju v subore
/home/OS/predtest/vstupy-2/timem11.txt
Cislo je suvisla postupnost cislic.

VYSLEDOK 802949

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy-2/timem11.txt | tr -c '[:digit:]' '\n' | sort | awk '{a=a+$1} END{print a}'
RIESENIE_KONIEC
======================================================================
PRIKLAD 10

Zistite, kolko pouzivatelov ma nastavenu prihlasovaciu skupinu os2003
Uvazujte vsetkych pouzivatelov, ktori maju na stroji konto.

VYSLEDOK 0

RIESENIE_ZACIATOK
cat /etc/passwd | awk -F ":" '{print $4}' | grep '525' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 11

Zistite, kolko krat sa vyskytuje v subore
/home/OS/predtest/vstupy-2/ccero10.txt
slovo, ktore sa v nom vyskytuje najcastejsie.
Slovo je postupnost znakov oddelena jednou alebo viacerymi medzerami.

VYSLEDOK 258

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy-2/ccero10.txt | tr -s ' ' '\n' | sort | uniq -c | sort | tail -1 | awk '{print $1}'
RIESENIE_KONIEC
======================================================================
PRIKLAD 12

Zistite, kolko pouzivatelov stroja osa ma meno Martin
Uvazujte vsetkych pouzivatelov, ktori maju na stroji konto.

VYSLEDOK 6

RIESENIE_ZACIATOK
cat /etc/passwd | grep -w 'Martin' | awk -F ":" '{print $5}' | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 13

Najdite najdlhsie slovo v subore
/home/OS/predtest/vstupy-2/11027.txt
Slovo je postupnost znakov oddelena jednou alebo viacerymi medzerami.

VYSLEDOK (http://www.ibiblio.org/gutenberg/1/1/0/2/11027/11027-h/11027-h.htm)

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy-2/11027.txt | tr -s ' ' '\n' | awk '{if (length > max) {max=length; sl=$1}} END{print sl}'
RIESENIE_KONIEC
======================================================================
PRIKLAD 14

Kolko roznych pouzivatelov sa prihlasilo v utorok ?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy-2/wtmp.03Apr
Uvazujte len ukoncene prihlasenia.

moje 
last -f /home/OS/predtest/vstupy-2/wtmp.03Apr | grep ' Tue ' | awk '{print $1}' | sort | uniq
VYSLEDOK 205
last | grep ')$' | cut -f1 -d ' ' | sort | uniq -c | sort -n +0 | awk '{print $1}'
RIESENIE_ZACIATOK
last -f /home/OS/predtest/vstupy-2/wtmp.03Apr | sort | awk '{if ($4 == "Tue") print $1 }' | uniq | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 15

Zistite, ktory pouzivatel sa hlasi na osu z najvacsieho mnozstva roznych strojov
a uvedte pocet tychto strojov.
Uvazujte kazde prihlasenie samostatne.
Pouzite prikaz last a ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy-2/wtmp.04Apr
Ignorujte prihlasenia, pre ktore nepoznate adresu stroja.

VYSLEDOK 34

RIESENIE_ZACIATOK
last -f /home/OS/predtest/vstupy-2/wtmp.04Apr | awk 'NF>9 {print $1,$3}' | sort | uniq | awk '{print $1}' | sort | uniq -c | sort -n | tail -1 | awk '{print $1}'
RIESENIE_KONIECs
======================================================================
PRIKLAD 16

Zistite, kolko roznych pouzivatelov sa hlasi na osu v noci (teda cas prihlasenia je
od 22:00 do 05:00).
Pouzite prikaz last a ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy-2/wtmp.03May
Uvazujte len jednotlive, ukoncene prihlasenia.

VYSLEDOK 186

RIESENIE_ZACIATOK
last -f /home/OS/predtest/vstupy-2/wtmp.03May | sort | awk '$8 ~ /-/ { print($1":"$7) }' | awk -F ":" '{ if (($2 < 5)||($2 > 21)) {print($1) } }' | sort | uniq | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 17

Kolko roznych pouzivatelov bolo prihlasenych kratsie ako 1 den?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy-2/wtmp.02Feb
Uvazujte len jednotlive, ukoncene prihlasenia.

VYSLEDOK 315

RIESENIE_ZACIATOK
last -s -f /home/OS/predtest/vstupy-2/wtmp.02Mar | awk '$7 ~ /-/ || $8 ~ /-/' | tr ')' ' ' | awk '{if ($NF<86400) print $1}' | sort | uniq | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 18

Kolko roznych pouzivatelov bolo prihlasenych v systeme?
Ako zdroj udajov pouzite subor
/home/OS/predtest/vstupy-2/wtmp.02Mar
Uvazujte len ukoncene prihlasenia.

VYSLEDOK 315

RIESENIE_ZACIATOK
last -f /home/OS/predtest/vstupy-2/wtmp.02Mar | awk '$7 ~ /-/ || $8 ~ /-/ {print $1}' | sort | uniq | wc -l
RIESENIE_KONIEC
======================================================================
PRIKLAD 19

Zistite, ake bolo priemerne bodove hodnotenie studentov z cviceni.
(stlpec Cvicenia).
Vsetky cisla zaokruhlite na cele cisla nadol.
Pouzite udaje zo suboru
/home/OS/predtest/vstupy-2/skuska2003.out

VYSLEDOK 37

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy-2/skuska2003.out | tail -n +3 | awk '{sm=sm + int($5); r++;} END {print int(sm/r)}' 
RIESENIE_KONIEC
======================================================================
PRIKLAD 20

Zistite, kolko studentov ziskalo zapocet.
Pouzite udaje zo suboru
/home/OS/predtest/vstupy-2/vysledky2001.out

VYSLEDOK 245

RIESENIE_ZACIATOK
cat /home/OS/predtest/vstupy-2/vysledky2001.out | awk -v x=0 '/XXXXX/ {if ($NF =="Z") x++} END { print x} '
RIESENIE_KONIEC
