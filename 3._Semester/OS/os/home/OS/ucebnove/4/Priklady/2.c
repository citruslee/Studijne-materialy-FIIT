#include <stdio.h>

/* Jednosmerna komunikacia z dvoch zdrojov potomok1, potomok2 -> rodic */

struct message {int src; int id; char text[10];} msg;

potomok(int src, int fd)
{
	int i;

	msg.src = src;
	for (i = 1; i < 10; i++) {
		msg.id = i;
		sprintf(msg.text, "text%d", i);
		write(fd, &msg, sizeof(msg));
		printf("Zaslana sprava %d od %d: %s\n", msg.id, msg.src, msg.text);
		sleep(1);
	}
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

			potomok(1, rura[1]);

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

			potomok(2, rura[1]);

			close(rura[1]);

			exit(0);
			break;
		default:	/* rodic */
	}

	close(rura[1]);		/* <----- aby necakal sam na seba */

	while (read(rura[0], &msg, sizeof(msg)) > 0)
		printf("Prijata sprava %d od %d: %s\n", msg.id, msg.src, msg.text);

	wait(&status);
	wait(&status);

	exit(0);
}
