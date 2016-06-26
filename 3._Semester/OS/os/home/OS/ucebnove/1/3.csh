#! /bin/csh

set vsetci = `who | cut -c1-8 | sort`

if ($#vsetci == 0) exit

set p = $vsetci[1]
@ i = 1
shift vsetci

while ($#vsetci > 0)
	if ($p == $vsetci[1]) then
		@ i ++
	else
		echo "$i	$p"
		set p = $vsetci[1]
		@ i = 1
	endif
	shift vsetci
end
echo "$i	$p"

who | cut -c1-8 | sort | uniq -c
