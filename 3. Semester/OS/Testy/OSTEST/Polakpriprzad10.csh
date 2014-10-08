#! /bin/csh
#
# Meno:Tomas Polak	
# Kruzok:14
# Datum:03.11.2005
# Zadanie: zadanie10
#
# Text zadania:
# V zadanych suboroch uvedenych ako argumenty najdite riadok (riadky)
# s najvacsim poctom slov a tieto riadky vypiste.
# Ak nebude uvedeny ako argument ziadny subor, prehladava sa standardny vstup.
# Ak bude skript spusteny s prepinacom -p <pocet>, hlada riadky s poctom slov
# vacsim ako <pocet>.
# Syntax:
# zadanie10.csh [-h] [-p <pocet>] [cesta ...]
# Vystup ma tvar:
# Output: '<subor>: <riadok>'
# Tip:
# "`cat ...`"
#
# Program musi osetrovat pocet a spravnost argumentov. Program musi mat help,
# ktory sa vypise pri zadani argumentu -h a ma tvar:
# Meno programu (C) meno autora
#
#Usage: <meno_programu> <arg1> <arg2> ...
#    <arg1>: xxxxxx
#    <arg2>: yyyyy
#
# Korektny vystup programu musi ist na standardny vystup (stdout).
# Chybovy vystup programu by mal ist na chybovy vystup (stderr).
# Chybovy vystup musi mat tvar (vratane apostrofov):
# Error: 'adresar, subor, ... pri ktorom nastala chyba': popis chyby ...
# Ak program pouziva nejake pomocne vypisy, musia mat tvar:
# Debug: vypis ...
#
# Poznamky: (sem vlozte pripadne poznamky k vypracovanemu zadaniu)
#
# Riesenie:

set hitchars
unset debug
set pocet
@ counter = 1
@ priznak = 0

while ($#argv>0)
	switch ("$argv[1]")
		case -h:
				echo "Usage: zadanie10.csh [-h] [-p <pocet>] [cesta ...]"
                echo "   -h: Vypise tento help"
                echo "   -p<pocet>: hlada riadky s poctom slov viac ako <pocet> znakov"
                exit 0
                breaksw
        case -p:
        		shift
        		if(! $#argv) then
        			goto errd
        		endif
        		
        		#test ci je argument cislo
        		expr "$argv[1]" + 1 >& /dev/null
        		if ($status != 0)then
        			goto errd
        		endif
        		
        		@ pocet =$argv[1]
        		@ priznak = 1
        		echo "Debug: Hladam riadky s poctom slov viac ako $pocet"
        		
        		breaksw
        		
        		errd:
        			echo "Error: Za prepinacom -p musi nasledovat cislo!"
        			exit 1
        			
        default:
        		break
        endsw
    shift
end		

# vytvori zoznam suborov, ktore sa maju prehladavat
 set subory = ()
 
 while ($#argv > 0)
  set subory = ($subory:q "$argv[1]")
  shift
 end
 
 while ($#subory > 0)
 	cat "$subory[1]"
 	shift subory
 end




