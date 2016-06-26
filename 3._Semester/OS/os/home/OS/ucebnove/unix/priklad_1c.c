/*
 * Napiste program, ktory v zadanom adresari, uvedenom ako argument, najde
 * vsetky obycajne subory a v nich zisti pocet riadkov, na ktorych sa nachadza
 * zadany retazec. Na najdenie tychto riadkov pouzite (povinne) program grep 
 * s pripadnymi prepinacmi a jeho vystup citajte cez ruru.
 */
 
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/dir.h>		// direct - zastarale
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

#include <sys/syslimits.h>	// PATH_MAX, NAME_MAX

char *progname;
char *retazec;

void Help();
void SearchDir(char *dirname, char *pattern);
int Count(char *filename, char *pattern);
 
void main(int argc, char *argv[]) 
{
	int i;
 	
	progname = argv[0];
	argc--; argv++;
	if (argc > 0 && ! strcmp(argv[0], "-h")) Help();

	if(argc < 1) {
		fprintf(stderr, "Error: nezadany retazec\n");
		exit(1);
	}

	retazec = argv[argc-1];

	if (argc == 1)
		SearchDir(".", retazec);
	else
		for (i = 0; i < argc-1; i++)
			SearchDir(argv[i], argv[argc-1]);
}
 
void Help() 
{
	printf("Pouzitie: %s [-h] [adresar ...] retazec\n", progname);
	exit(0);
}

void SearchDir(char *dirname, char *pattern)
{
	DIR *dp;
	struct dirent *dir;
	char path[PATH_MAX];
	struct stat filestat;
			
	if ((dp = opendir(dirname)) == NULL) {
		fprintf(stderr,"Error: '%s': neda sa otvorit\n", dirname);
//		exit(1);
	}

	while ((dir = readdir(dp)) != NULL) {
//		if (dir->d_ino == 0) continue;
		if (! strcmp(dir->d_name, ".") || \
		    ! strcmp(dir->d_name, "..")) continue;

		sprintf(path, "%s/%s", dirname, dir->d_name);

		stat(path, &filestat);
		
		if (S_ISDIR(filestat.st_mode)) {
			SearchDir(path, pattern);
			continue;
		}
		
		if (! S_ISREG(filestat.st_mode)) continue;	
		
		printf("Output: '%s: %d'\n", path, Count(path, pattern));
	}

	closedir(dp);
}

int Count(char *filename, char *pattern)
{
	int pd[2];
	int count;
	FILE *p;

	count = -1;
	if (pipe(pd) == -1) {
		fprintf(stderr, "Error: nemozem vytvorit ruru\n");
		exit(1);
	}

	switch (fork()) {
		case -1:
			fprintf(stderr, "Error: nemozem vykonat fork\n");
			exit(1);

		case 0:		// potomok
			close(pd[0]);
			close(1);
			dup(pd[1]);
			close(pd[1]);
			
			execlp("/usr/bin/grep", "grep", "-c", pattern, filename, NULL);
			fprintf(stderr, "Error: nemozem spustit grep");
			exit(1);

		default:	// rodic
			close(pd[1]);

			if ((p = fdopen(pd[0], "r")) == NULL) {
				fprintf(stderr, "Error: nemozem urobit fdopen\n");
				exit(1);
			}
			if (fscanf(p, "%d", &count) != 1) {
				fprintf(stderr, "Error: nemozem precitat vysledok grep-u\n");
				exit(1);
			}
			wait(NULL);
	}

	return count;
}
