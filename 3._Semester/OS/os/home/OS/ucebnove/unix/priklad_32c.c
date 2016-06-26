/*
 * Napiste program, ktory ma ako argumenty 2 subory vstup1 a vstup2 a na 
 * standardny vystup zapise postupne prve, druhe, ... riadky z oboch vstupnych 
 * suborov. Pritom vsetky pismena zo suboru vstup1 skonvertuje na velke
 * a vsetky pismena zo suboru vstup2 skonvertuje na male. Na konverziu pouzite
 * (povinne) program tr (napr. tr '[:lower:]' '[:upper:]').
 */
 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

char *progname;

void Help();
FILE *Spusti(int in, int out[2], int which);

void main(int argc, char *argv[])
{
	int f1, f2;
	int out1[2], out2[2];
	FILE *p1, *p2;
	char buf[1024];
	int end;
 	
	progname = argv[0];
	argc--; argv++;
	if (argc > 0 && ! strcmp(argv[0], "-h")) Help();

	if( argc < 2 || argc % 2 != 0) {
		fprintf(stderr, "Error: nespravny pocet argumentov\n");
		exit(1);
	}

	/* cyklus cez vsetky dvojice suborov */
	while (argc > 1){
		if ((f1 = open(argv[0], O_RDONLY)) == -1) {
			fprintf(stderr,"Error: '%s': Nemozem otvorit subor\n", argv[0]);
			exit(0);
		}
		pipe(out1);
		p1 = Spusti(f1, out1, 1);

		if ((f2 = open(argv[1], O_RDONLY)) == -1) {
			fprintf(stderr,"Error: '%s': Nemozem otvorit subor\n", argv[1]);
			exit(0);
		}
		pipe(out2);
		p2 = Spusti(f2, out2, 2);

		/* cyklus cez vsetky riadky */
		end = 0;
		while(! end) {
			end = 1;
			if (fgets(buf, sizeof(buf), p1)) {
				end = 0;
				fputs(buf, stdout);
			}
			if (fgets(buf, sizeof(buf), p2)) {
				end = 0;
				fputs(buf, stdout);
			}
		}
		fclose(p1); fclose(p2);
		wait(NULL); wait(NULL);

		/* posun argumenty */
		argv += 2; argc -= 2;
	}
}
 
void Help()
{
	printf("Pouzitie: %s [-h] <subor1> <subor2> [<subor1> <subor2>] ...\n", progname);
	exit(0);
}

FILE *Spusti(int in, int out[2], int which)
{
	FILE *p;

	switch (fork()) {
		case 0:
			close(0); dup(in);  close(in);
			close(1); dup(out[1]); close(out[1]); close(out[0]);
			if (which == 1)
				execlp("tr", "tr", "[:lower:]", "[:upper:]", NULL);
			else
				execlp("tr", "tr", "[:upper:]", "[:lower:]", NULL);
			fprintf(stderr, "Error: nemozem spustit tr");
			exit(1);
		case -1:
			fprintf(stderr, "Error: nemozem vykonat fork\n");
			exit(1);
		default:
			close(in);
			close(out[1]);
	}
	if ((p = fdopen(out[0], "r")) == NULL) {
		fprintf(stderr, "Error: nemozem urobit fdopen\n");
		exit(1);
	}
	return(p);
}
