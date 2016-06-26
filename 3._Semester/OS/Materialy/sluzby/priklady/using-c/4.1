/*
 * Non-BSD systems only.
 */
#include <sys/types.h>
#include <sys/dir.h>
#include <stdio.h>

main()
{
    FILE *fp;
    struct direct dir;
    int n;

    if ((fp = fopen(".", "r")) == NULL) {
        perror("current directory");
        exit(1);
    }

	/*
	 * Read directory entries.  Since we're reading
	 * entries one at a time, we use the fread routine,
	 * which buffers them internally.  Don't use the
	 * low-level read to do things this way, since
	 * reading very small quantities of data (16 bytes)
	 * at a time is very inefficient.
	 */
    while ((n = fread(&dir, sizeof(dir), 1, fp)) > 0) {
        /*
         * Skip removed files.
         */
        if (dir.d_ino == 0)
            continue;

        /*
         * Make sure we print no more than DIRSIZ
         * characters.
         */
        printf("%.*s\n", DIRSIZ, dir.d_name);
    }

    fclose(fp);
    exit(0);
}

