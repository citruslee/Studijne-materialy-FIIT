/*
 * 
 */
#include <stdio.h>

struct record {
    int uid;
    char login[9];
};

char *logins[] = { "user1", "user2", "user3",
                   "user4", "user5" };

main()
{
    int i;
    FILE *fp;
    struct record rec;

    /*
     * Open the data file for writing.
     */
    if ((fp = fopen("datafile", "w")) == NULL) {
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
        putrec(fp, i, &rec);
    }

    fclose(fp);
    exit(0);
}

/*
 * putrec--write the record in the i'th position.
 */
putrec(fp, i, r)
int i;
FILE *fp;
struct record *r;
{
    /*
     * Seek to the i'th position from the beginning
     * of the file.
     */
    fseek(fp, (long) i * sizeof(struct record), 0);

    /*
     * Write the record.  We want to write one
     * object the size of a record structure.
     */
    fwrite(r, sizeof(struct record), 1, fp);
}

