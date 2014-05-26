#include <termio.h>
#include <stdio.h>

main(argc, argv)
int argc;
char **argv;
{
    struct termio tio, tin;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s file [file ...]\n", *argv);
        exit(1);
    }

    /*
     * In real life we'd check the return value of
     * this, since if the input is redirected from a
     * file it will fail.  We are assuming the
     * terminal is always connected to the standard
     * input.
     */
    ioctl(0, TCGETA, &tio);

    tin = tio;
    tin.c_lflag &= ~ECHO;      /* turn off ECHO   */
    tin.c_lflag &= ~ICANON;    /* turn off ICANON */

    /*
     * Emulate CBREAK mode.
     */
    tin.c_cc[VMIN] = 1;
    tin.c_cc[VTIME] = 0;

    /*
     * Set the new modes.  Again we ignore return
     * values.
     */
    ioctl(0, TCSETA, &tin);

    while (--argc)
        more(*++argv);

    /*
     * Reset the old tty modes.
     */
    ioctl(0, TCSETA, &tio);

    exit(0);
}

/*
 * more--display the file.
 */
more(file)
char *file;
{
    FILE *fp;
    int line;
    char linebuf[1024];

    if ((fp = fopen(file, "r")) == NULL) {
        perror(file);
        return;
    }

    /*
     * Print 22 lines at a time.
     */
    for (;;) {
        line = 1;
        while (line < 22) {
            /*
             * If end-of-file, let them hit a key one
             * more time and then go back.
             */
            if (fgets(linebuf, sizeof(linebuf), fp) == NULL) {
                fclose(fp);
                prompt();
                return;
            }

            fwrite(linebuf, 1, strlen(linebuf), stdout);
            line++;
        }

        prompt();
    }
}

/*
 * prompt--prompt for a character.
 */
prompt()
{
    char answer;

    printf("Type any character for next page: ");
    answer = getchar();
    putchar('\n');
}

