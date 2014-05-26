#include <stdio.h>
#include <utmp.h>
#include <pwd.h>

#define UTMP    "/etc/utmp"
#define NAMELEN	8

main()
{
    FILE *fp;
    struct utmp u;
    struct passwd *p;
    char tmp[NAMELEN+1];
    struct passwd *getpwnam();

    if ((fp = fopen(UTMP, "r")) == NULL) {
        perror(UTMP);
        exit(1);
    }

    /*
     * For each entry...
     */
    while (fread(&u, sizeof(u), 1, fp) != NULL) {
        /*
         * Skip non-logged in ports.
         */
        if (u.ut_name[0] == NULL)
            continue;

        /*
         * Make sure name is null-terminated.
         */
        strncpy(tmp, u.ut_name, NAMELEN);

        /*
         * Skip non-existent users (shouldn't
         * be any).
         */
        if ((p = getpwnam(tmp)) == NULL)
            continue;

        /*
         * Print the line.  ctime() converts the time
         * to ASCII format, it is described in Chapter
         * 7, Telling Time and Timing Things. We
         * ignore the format of the gecos field and
         * just print the first 30 characters; in real
         * life we would stop at a comma or some such.
         */
        printf("%-10.8s %-10.8s %-30.30s %s", u.ut_name,
	    u.ut_line, p->pw_gecos, ctime(&u.ut_time));
    }

    fclose(fp);
    exit(0);
}

