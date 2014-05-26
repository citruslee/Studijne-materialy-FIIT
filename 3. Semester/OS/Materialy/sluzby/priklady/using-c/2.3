#include <stdio.h>

main(argc, argv)
int argc;
char **argv;
{
    int n;
    FILE *from, *to;
    char buf[BUFSIZ];

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
     * Note that we only write the number of characters fread 
     * read in, rather than always writing BUFSIZ characters.
     */
    while ((n = fread(buf, sizeof(char), BUFSIZ, from)) > 0)
        fwrite(buf, sizeof(char), n, to);

    /*
     * Now close the files.
     */
    fclose(from);
    fclose(to);
    exit(0);
}

