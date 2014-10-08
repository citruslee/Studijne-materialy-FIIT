
/*
 * Non-BSD systems only.
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <stdio.h>

#define DIRSIZE(e)     (min(strlen(e->d_name), DIRSIZ))

typedef struct {
    int    d_fd;
} DIR;

char *malloc();

DIR *
opendir(dir)
char *dir;
{
    struct stat stbuf;
    DIR *dp = (DIR *) malloc(sizeof *dp);

    if ((dp->d_fd = open(dir, 0)) < 0)
        return(0);

    if ((fstat(dp->d_fd, &stbuf) < 0) ||
        ((stbuf.st_mode & S_IFDIR) == 0)) {
        closedir(dp);
        return(0);    /* this isn't a directory! */
    }

    return(dp);
}

closedir(dp)
DIR *dp;
{
    (void) close(dp->d_fd);
    free((char *) dp);
}

struct direct *
readdir(dp)
DIR *dp;
{
    static struct direct dir;

    do {
        if (read(dp->d_fd, &dir, sizeof(dir)) != sizeof(dir))
            return(0);
    } while (dir.d_ino == 0);

    return(&dir);
}

/*
 * Scandir returns the number of entries or -1 if the
 * directory cannot be opened or malloc fails.
 */
scandir(dir, nmptr, select, compar)
char *dir;
char ***nmptr;
int (*select)();
int (*compar)();
{
    DIR *dirp;
    char **array;
    char **realloc();
    struct direct *ent;
    unsigned int nalloc = 10, nentries = 0;

    if ((dirp = opendir(dir)) == NULL)
        return(-1);

    array = (char **) malloc(nalloc * sizeof (char *));

    if (array == NULL)
        return(-1);

    while ((ent = readdir(dirp)) != NULL) {
        if (select && ((*select)(ent->d_name) == 0))
            continue;

        if (nentries == nalloc) {
            array = realloc(array, (nalloc += 10) * sizeof(char *));

            if (array == NULL)
                return(-1);
        }

        array[nentries] = (char *) malloc(DIRSIZE(ent)+1);
        strncpy(array[nentries], ent->d_name, DIRSIZE(ent));
        array[nentries][DIRSIZE(ent)] = NULL;
        nentries++;
    }

    closedir(dirp);

    if ((nentries + 1) != nalloc)
        array = realloc(array, ((nentries + 1) * sizeof (char *)));

    if (compar != 0)
        qsort(array, nentries, sizeof(char **), compar);

    *nmptr = array;
    array[nentries] = 0;     /* guaranteed 0 pointer */

    return(nentries);
}

alphasort(a, b)
char **a, **b;
{
    return(strcmp(*a, *b));
}
