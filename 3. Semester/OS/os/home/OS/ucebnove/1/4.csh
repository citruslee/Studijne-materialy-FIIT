#! /bin/csh

unset ajcestu
while ($#argv > 0)
	switch ($argv[1])
		case -h:
			echo "Pouzitie: $0 [-h] [-p] [adresar]"
			exit
		case -p:
			set ajcestu
			breaksw
		default:
			breaksw; break
	endsw
	shift
end

if ($#argv == 0) then
	set dir = .
else
	set dir = $argv[1]
endif

foreach f ("`find $dir -type f`")
	if ("`file $f`" =~ *text*) then
		if ($?ajcestu) then
			echo "$f:t	v	$f:h"
		else
			echo "$f:t"
		endif
	endif
end
