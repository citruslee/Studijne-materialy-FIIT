/*
 * If you're on System V, change <sys/file.h> to <sys/fcntl.h>.
 */
#include <sys/file.h>

struct record {
    int uid;
    char login[9];
};

char *logins[] = { "user1", "user2", "user3",
                   "user4", "user5" };

main()
{
    int i, fd;
    struct record rec;

    /*
     * Open the data file for writing.
     */
    if ((fd = open("datafile", O_WRONLY | O_CREAT, 0644)) < 0) {
        perror("datafile");
        exit(1);
    }

    /*
     * For each user, going backwards...
     */
    for (i = 4; i >= 0; i--) {
        /*
         * Create the record.
         */
        rec.uid = i;
        strcpy(rec.login, logins[i]);

        /*
         * Output the record.  Notice we pass the
         * address of the structure.
         */
        putrec(fd, i, &rec);
    }

    close(fd);
    exit(0);
}

/*
 * putrec--write the record in the i'th position.
 */
putrec(fd, i, r)
int i, fd;
struct record *r;
{
    /*
     * Seek to the i'th position from the beginning
     * of the file.
     */
    lseek(fd, (long) i * sizeof(struct record), L_SET);

    /*
     * Write the record.  We want to write one
     * object the size of a record structure.
     */
    write(fd, r, sizeof(struct record));
}

