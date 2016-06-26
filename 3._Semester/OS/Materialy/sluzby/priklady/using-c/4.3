#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <stdio.h>

char *modes[] = {
    "---", "--x", "-w-", "-wx",
    "r--", "r-x", "rw-", "rwx"
};

main(argc, argv)
int argc;
char **argv;
{
    struct stat sbuf;

    /*
     * If no arguments, list current directory.
     */
    if (argc < 2) {
        list(".");
        exit(0);
    }

    /*
     * Process arguments.
     */
    while (--argc) {
        /*
         * See what the file is.
         */
        if (stat(*++argv, &sbuf) < 0) {
            perror(*argv);
            continue;
        }

        /*
         * If it's a directory we list it,
         * otherwise just print the info about
         * the file.
         */
        if ((sbuf.st_mode & S_IFMT) == S_IFDIR)
            list(*argv);
        else
            printout(".", *argv);
    }

    exit(0);
}

/*
 * list--read a directory and list the files it
 *        contains.
 */
list(name)
char *name;
{
    DIR *dp;
    struct direct *dir;

    /*
     * Open the directory.
     */
    if ((dp = opendir(name)) == NULL) {
        fprintf(stderr, "%s: cannot open.\n", name);
        return;
    }

    /*
     * For each entry...
     */
    while ((dir = readdir(dp)) != NULL) {
        /*
         * Skip removed files.
         */
        if (dir->d_ino == 0)
            continue;

        /*
         * Print it out.
         */
        printout(name, dir->d_name);
    }

    closedir(dp);
}

/*
 * printout--print out the information about
 *            a file.
 */
printout(dir, name)
char *dir, *name;
{
    int i, j;
    char perms[10];
    struct stat sbuf;
    char newname[1024];

    /*
     * Make full path name, so
     * we have a legal path.
     */
    sprintf(newname, "%s/%s", dir, name);

    /*
     * At this point we know the file exists,
     * so this won't fail.
     */
    stat(newname, &sbuf);

    /*
     * Print size in kbytes.
     */
    printf("%5d ", (sbuf.st_size + 1023) / 1024);

    /*
     * Get the file type.  For convenience (and to
     * make this example universal), we ignore the
     * other types which are version-dependent.
     */
    switch (sbuf.st_mode & S_IFMT) {
    case S_IFREG:    putchar('-'); break;
    case S_IFDIR:    putchar('d'); break;
    case S_IFCHR:    putchar('c'); break;
    case S_IFBLK:    putchar('b'); break;
    default:         putchar('?'); break;
    }

    /*
     * Get each of the three groups of permissions
     * (owner, group, world).  Since they're just
     * bits, we can count in binary and use this
     * as a subscript (see the modes array, above).
     */
    *perms = NULL;
    for (i = 2; i >= 0; i--) {
        /*
         * Since we're subscripting, we don't
         * need the constants.  Just get a
         * value between 0 and 7.
         */
        j = (sbuf.st_mode >> (i*3)) & 07;

        /*
         * Get the perm bits.
         */
        strcat(perms, modes[j]);
    }

    /*
     * Handle special bits which replace the 'x'
     * in places.
     */
    if ((sbuf.st_mode & S_ISUID) != 0)
        perms[2] = 's';
    if ((sbuf.st_mode & S_ISGID) != 0)
        perms[5] = 's';
    if ((sbuf.st_mode & S_ISVTX) != 0)
        perms[8] = 't';

    /*
     * Print permissions, number of links,
     * user and group ids.
     */
    printf("%s%3d %5d/%-5d ", perms, sbuf.st_nlink, sbuf.st_uid,
        sbuf.st_gid);

    /*
     * Print the size of the file in bytes,
     * and the last modification time.  The
     * ctime routine converts a time to ASCII;
     * it is described in Chapter 7, Telling
     * Time and Timing Things.
     */
    printf("%7d %.12s ", sbuf.st_size, ctime(&sbuf.st_mtime)+4);

    /*
     * Finally, print the filename.
     */
    printf("%s\n", name);
}

