#include <stdio.h>

#define NSTRS      10         /* number of strings     */
#define STRLEN     16         /* length of each string */

char strs[NSTRS][STRLEN];     /* array of strings      */

main()
{
    int i;
    extern int compare1(), compare2();

    /*
     * Prompt the user for NSTRS strings.
     */
    for (i = 0; i < NSTRS; i++) {
        printf("Enter string #%d: ", i);
        gets(strs[i]);
    }

    /*
     * Sort the strings into ascending order.  There
     * are NSTRS array elements, each one is STRLEN
     * characters long.  Note we give the size of
     * the array element, not the length of the
     * string in it.
     */
    qsort(strs, NSTRS, STRLEN, compare1);

    /*
     * Print the strings.
     */
    printf("\nSorted in ascending order:\n");

    for (i = 0; i < NSTRS; i++)
        printf("\t%s\n", strs[i]);

    /*
     * Now sort the strings in descending order.
     */
    qsort(strs, NSTRS, STRLEN, compare2);

    printf("\nSorted in descending order:\n");

    for (i = 0; i < NSTRS; i++)
        printf("\t%s\n", strs[i]);

    exit(0);
}

/*
 * compare1--compare a and b, and return less than,
 *            greater than, or equal to zero.  Since
 *            we are comparing character strings, we
 *            can just use strcmp to do the work for us.
 */
compare1(a, b)
char *a, *b;
{
    return(strcmp(a, b));
}

/*
 * compare2--this compares a and b, but is used for
 *            sorting in the opposite order.  Thus it
 *            returns the opposite of strcmp.  We can
 *            simulate this by simply reversing the
 *            arguments when we call strcmp.
 */
compare2(a, b)
char *a, *b;
{
    return(strcmp(b, a));
}

