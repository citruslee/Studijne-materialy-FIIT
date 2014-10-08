#include <stdio.h>

/* Jednosmerna komunikacia rodic -> potomok */

main()
{
	int rura[2];
	struct message {int id; char text[10];} msg;
	int i;
	int status;

	pipe(rura);

	switch(fork()) {
		case -1:	/* chyba */
			exit(1);
			break;
		case 0:		/* potomok */
			close(0);
			dup(rura[0]);		/* aby cital z rury ako zo standardneho vstupu */
			close(rura[0]);
			close(rura[1]);		/* aby necakal sam na seba a nemylil zapisujuceho */

			sleep(1);		/* <----- aby pockal */

			while (read(0, &msg, sizeof(msg)) > 0)
				printf("Prijata sprava %d: %s\n", msg.id, msg.text);

			exit(0);
			break;
		default:	/* rodic */
			close(1);
			dup(rura[1]);		/* aby zapisoval do rury ako do standardneho vystupu */
			close(rura[0]);
			close(rura[1]);		/* aby nemylil citajuceho */

			for (i = 1; i < 10; i++) {
				msg.id = i;
				sprintf(msg.text, "text%d", i);
				write(1, &msg, sizeof(msg));
				fprintf(stderr, "Zaslana sprava %d: %s\n", msg.id, msg.text);
			}

			close(1);		/* <----- aby potomok vedel, ze uz nema co citat */

			wait(&status);		/* <----- aby pockal na skoncenie potomka */

			exit(0);
	}
}
