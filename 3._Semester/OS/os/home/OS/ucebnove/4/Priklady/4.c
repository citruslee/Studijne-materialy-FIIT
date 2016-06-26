#include <stdio.h>

/* Jednosmerna komunikacia medzi dvoma producentmi a dvoma konzumentmi
   producent1, producent2 -> konzument1, konzument2 */

struct message {int src; int id; char text[10];} msg;

producent(int meno, int fd)
{
	int i;

	msg.src = meno;
	for (i = 1; i < 10; i++) {
		msg.id = i;
		sprintf(msg.text, "text%d", i);
		write(fd, &msg, sizeof(msg));
		printf("Zaslana sprava %d od producenta %d: %s\n", msg.id, meno, msg.text);
		sleep(1);
	}
}

konzument(int meno, int fd)
{
	while (read(fd, &msg, sizeof(msg)) > 0)
		printf("Prijata sprava %d od %d konzumentom %d: %s\n", msg.id, msg.src, meno, msg.text);
}

main()
{
	int rura[2];
	int i;
	int status;

	pipe(rura);

	switch(fork()) {
		case -1:	/* chyba */
			exit(1);
			break;
		case 0:		/* potomok 1 */
			close(rura[0]);

			producent(1, rura[1]);

			close(rura[1]);

			exit(0);
			break;
		default:	/* rodic */
	}

	switch(fork()) {
		case -1:	/* chyba */
			exit(1);
			break;
		case 0:		/* potomok 2 */
			close(rura[0]);

			producent(2, rura[1]);

			close(rura[1]);

			exit(0);
			break;
		default:	/* rodic */
	}

	switch(fork()) {
		case -1:	/* chyba */
			exit(1);
			break;
		case 0:		/* potomok 3 */
			close(rura[1]);

			konzument(1, rura[0]);

			close(rura[0]);

			exit(0);
			break;
		default:	/* rodic */
	}

	switch(fork()) {
		case -1:	/* chyba */
			exit(1);
			break;
		case 0:		/* potomok 4 */
			close(rura[1]);

			konzument(2, rura[0]);

			close(rura[0]);

			exit(0);
			break;
		default:	/* rodic */
	}

	close(rura[0]);
	close(rura[1]);

	wait(&status);
	wait(&status);
	wait(&status);
	wait(&status);

	exit(0);
}
