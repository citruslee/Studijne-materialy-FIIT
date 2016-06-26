/* Change <sys/file.h> to <sys/fcntl.h> if you're on System V.
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
     * Check our arguments.  Note that to write the error
     * message we can't just use "%s" as we did in Example
     * 2-3; we have to write each string separately.
     */
    if (argc != 3) {
        write(2, "Usage: ", 7);
        write(2, *argv, strlen(*argv));
        write(2, " from-file to-file\n", 19);
        exit(1);
    }

    /*
     * Open the from-file for reading.
     */
    if ((from = open(argv[1], O_RDONLY)) < 0) {
        perror(argv[1]);
        exit(1);
    }

    /*
     * Open the to-file for appending.  If to-file does
     * not exist, open will create it with mode 644
     * (-rw-r--r--).  Note that we specify the mode
     * in octal, not decimal
     */
    if ((to = open(argv[2], O_WRONLY|O_CREAT|O_APPEND, 0644)) < 0) {
        perror(argv[2]);
        exit(1);
    }

    /*
     * Now read a buffer-full at a time from the from-file,
     * and write it to the to-file.  Note that we only
     * write the number of characters read read in,
     * rather than always writing 1024 characters.
     */
    while ((n = read(from, buf, sizeof(buf))) > 0)
        write(to, buf, n);

    /*
     * Now close the files.
     */
    close(from);
    close(to);
    exit(0);
}

