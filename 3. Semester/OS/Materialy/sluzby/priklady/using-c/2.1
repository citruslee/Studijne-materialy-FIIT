
#include <stdio.h>

main(argc, argv)
int argc;
char **argv;
{
    int c;
    FILE *from, *to;

    /*
     * Check our arguments.
     */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s from-file to-file\n", *argv);
        exit(1);
    }

    /*
     * Open the from-file for reading.
     */
    if ((from = fopen(argv[1], "r")) == NULL) {
        perror(argv[1]);
        exit(1);
    }

    /*
     * Open the to-file for appending.  If to-file does
     * not exist, fopen will create it.
     */
    if ((to = fopen(argv[2], "a")) == NULL) {
        perror(argv[2]);
        exit(1);
    }

    /*
     * Now read characters from from-file until we
     * hit end-of-file, and put them onto to-file.
     */
    while ((c = getc(from)) != EOF)
        putc(c, to);

    /*
     * Now close the files.
     */
    fclose(from);
    fclose(to);
    exit(0);
}
