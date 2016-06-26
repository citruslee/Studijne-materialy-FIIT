#include <stdio.h>

/* Obojsmerna komunikacia rodic <-> potomok */

main()
{
	int rura_k_potomkovi[2], rura_od_potomka[2];
	struct message {int id; char text[10];} msg;
	int i;
	int status;

	pipe(rura_k_potomkovi);
	pipe(rura_od_potomka);

	switch(fork()) {
		case -1:	/* chyba */
			exit(1);
			break;
		case 0:		/* potomok */
			close(0);
			dup(rura_k_potomkovi[0]);
			close(1);
			dup(rura_od_potomka[1]);
			close(rura_k_potomkovi[0]);
			close(rura_k_potomkovi[1]);
			close(rura_od_potomka[0]);
			close(rura_od_potomka[1]);

			while (read(0, &msg, sizeof(msg)) > 0) {
				sleep(1);
//				sprintf(msg.text, "odpoved%d", i);
				sprintf(msg.text, "odpoved%d", msg.id);
				write(1, &msg, sizeof(msg));
			}

			exit(0);
			break;
		default:	/* rodic */
			close(1);
			dup(rura_k_potomkovi[1]);
			close(0);
			dup(rura_od_potomka[0]);
			close(rura_k_potomkovi[0]);
			close(rura_k_potomkovi[1]);
			close(rura_od_potomka[0]);
			close(rura_od_potomka[1]);

			for (i = 1; i < 10; i++) {
				msg.id = i;
				sprintf(msg.text, "text%d", i);
				write(1, &msg, sizeof(msg));
				fprintf(stderr, "Zaslana sprava %d potomkovi: %s\n", msg.id, msg.text);

				read(0, &msg, sizeof(msg));
				fprintf(stderr, "Prijata sprava %d od potomka: %s\n", msg.id, msg.text);
			}

			close(1);		/* <----- aby potomok vedel, ze uz nema co citat */

			wait(&status);		/* <----- aby pockal na skoncenie potomka */

			exit(0);
	}
}
