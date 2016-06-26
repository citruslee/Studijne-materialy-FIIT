/*
 * For use with 4.2 and 4.3BSD systems.
 */
#include <sys/types.h>
#include <sys/dir.h>
#include <stdio.h>

main()
{
    DIR *dp;
    struct direct *dir;

    if ((dp = opendir(".")) == NULL) {
        fprintf(stderr, "cannot open directory.\n");
        exit(1);
    }

    /*
     * Read entries...
     */
    while ((dir = readdir(dp)) != NULL) {
        /*
         * Skip removed files.
         */
        if (dir->d_ino == 0)
            continue;

        printf("%s\n", dir->d_name);
    }

    closedir(dp);
    exit(0);
}

