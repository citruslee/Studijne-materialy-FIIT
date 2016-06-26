# pokusny soubor pro make

# pozadavek ladicich informaci
OPT=-O3

pozdravy: hlavni.c ahoj.o nazdar.o cao.o
	gcc ${OPT} ahoj.o nazdar.o cao.o hlavni.c -o $@

ahoj.o: ahoj.c ahoj.h nazdar.h cao.h max.h
	gcc ${OPT} -c ahoj.c

nazdar.o: nazdar.c nazdar.h cao.h max.h
	gcc ${OPT} -c nazdar.c

cao.o: cao.c cao.h max.h
	gcc ${OPT} -c cao.c
