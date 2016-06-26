/*
 * Napiste program, ktory vypise vsetkych pouzivatelov, ktori maju spustenych
 * viac ako 4 procesy.
 * Na zistenie spustenych procesov pouzite (povinne) vystup 
 * prikazu 'ps -Af' a tento citajte cez ruru.
 */
 
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#define MAX_USER_COUNT 256
 	
struct User {
	char UserName[16];
	int ProcCount;
} UserTab[MAX_USER_COUNT];

int LastUserIndex = 0;

void Help();
void Pocitaj(int pocet);

int IsInTable(char *u);
int AddUser(char *u);

void main(int argc, char * argv[])
{
	int o;
	int pocet = 4;
 
	opterr = 0;
	while ((o = getopt(argc, argv, "hp:")) != -1)
		switch (o) {
			case 'h':
				Help();
				exit(0);
			case 'p':
				pocet = atoi(optarg);
				if (pocet < 1) {
					fprintf(stderr, "Error: '%s': nespravny pocet\n", optarg);
					exit(1);
				}
				break;
			case '?':
			default:
				exit(1);
		}
	argc -= optind;
	argv += optind;

	Pocitaj(pocet);
}
 
void Help()
{
	printf("Pouzitie: priklad_13c [-h] [-p n]\n");
}

void Pocitaj(int pocet)
{
	int pid;
	int pipefd[2];
	FILE *f;
	int index;
	char line[1024];
	char name[16];

	if (pipe(pipefd) < 0) {
		fprintf(stderr, "Error: Nastala chyba pri vytvarani rury\n");
		exit(1);
	}
		
	if ((pid = fork()) == -1) {
		fprintf(stderr, "Error: Nastala chyba pri vytvarani potomka\n");
		exit(1);
	}
	 
	if (pid == 0) {		// potomok
		close(1);
		dup(pipefd[1]);
		close(pipefd[1]);
		close(pipefd[0]);

		execl("/bin/ps","ps","-aux",NULL);
		fprintf(stderr, "Error: Nastala chyba pri spustani prikazu /bin/ps\n");
		exit(1);
	}
 
	// rodic
 
	close(pipefd[1]);
	
	if ((f = fdopen(pipefd[0], "r")) == NULL) {
		fprintf(stderr, "Error: Nastala chyba pri prekonvertovavani handle z int na FILE *\n");
		exit(1);
	}
	
	fgets(line, sizeof(line), f);		// preskocime 1. riadok
	while (fgets(line, sizeof(line), f) != NULL) {
					 
		sscanf(line, "%s", name);
		
		if((index = IsInTable(name)) >= 0) {
			UserTab[index].ProcCount++;
		} else {
			if ((index = AddUser(name)) == -1) {
				fprintf(stderr, "Error: Tabulka pouzivatelov je plna\n");
				exit(1);
			}
		}
	}
 
	fclose(f);

	for (index = 0; index < LastUserIndex; index++)
		if (UserTab[index].ProcCount > pocet)
			printf("Output: '%s %d'\n", UserTab[index].UserName, UserTab[index].ProcCount); 
}


int IsInTable(char *name)
{
	int i;
	
	for(i = 0; i < LastUserIndex; i++)
		if (! strcmp(UserTab[i].UserName,name))
			return (i);
	return -1;
}

int AddUser(char *name)
{
	if (LastUserIndex == (MAX_USER_COUNT - 1)) {
		return -1;
	}
		
	strncpy(UserTab[LastUserIndex].UserName, name, 16);

	UserTab[LastUserIndex].ProcCount = 1;

	return LastUserIndex++;
}
