/*
  Tento program prida jeden subor k druhemu (append). Oba subory musia
  byt uvedene v command-line.
*/

/*
  Change <sys/file.h> to <sys/fcntl.h> if you're on System V.
*/

#include <sys/file.h>

main(argc, argv)
int argc;
char **argv;
{
    int n;
    int from, to;
    char buf[1024];

    /*
      Kontrola poctu argumentov...
     */
    if (argc != 3) {
        write(2, "Usage: ", 7);
        write(2, *argv, strlen(*argv));
        write(2, " from-file to-file\n", 19);
        exit(1);
    }

    /*
     * Otvorenie prveho suboru na citanie
     */
    if ((from = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        exit(1);
    }

    /*
       Otvorenie druheho suboru na zapis (append-mode). Ak
       zadany subor neexistuje, tak sa vytvori s modom 644
       (-rw-r--r--). Vsimnite si, ze mod sa specifikuje v
       osmickovej sustave.
     */
    if ((to = open(argv[2], O_WRONLY|O_CREAT|O_APPEND, 0644)) < 0) {
        perror(argv[2]);
        exit(1);
    }

    /*
       Teraz sa precita do bafra 'buf' tolko znakov, kolko sa da
       z prveho suboru (maximalne velkost bafra), a zapise sa do
       druheho suboru. Cely cyklus sa opakuje, az kym uz z prveho
       suboru nemozme citat (podla vsetkeho je uz cely precitany).
     */
    while ((n = read(from, buf, sizeof(buf))) > 0)
        write(to, buf, n);

    /*
      Subory treba uzavriet.
     */
    close(from);
    close(to);
    exit(0);
}

