#! /bin/csh

set znaky = (d g f 3 6 s 4 w h f 6 0 b d t y 3 6 s f)

set cisla   = ()
set pismena = ()
@ pc = 0
@ pp = 0

foreach znak ($znaky)
#	if ($znak >= 1 && $znak <= 9) then
	if ($znak == 0 || $znak == 1 || $znak == 2 || $znak == 3 || \
	    $znak == 4 || $znak == 5 || $znak == 6 || $znak == 7 || \
	    $znak == 8 || $znak == 9) then
		set cisla = ($cisla $znak); @ pc ++
	else
		set pismena = ($pismena $znak); @ pp ++
	endif
end

echo Pismena: $pismena Pocet: $pp $#pismena
echo Cisla: $cisla Pocet: $pc $#cisla
