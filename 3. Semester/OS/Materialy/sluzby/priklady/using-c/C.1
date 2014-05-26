#include <sys/param.h>
#include <sys/time.h>
#include <sys/file.h>
#include <nlist.h>
#include <stdio.h>

/*
 * We declare an array of nlist structures,
 * and initialize them to the names of the
 * variables we want.  The last entry is
 * to terminate the list.
 */
struct nlist nl[] = {
#define X_BOOTTIME     0
    {    "_boottime" },
#define X_AVENRUN      1
    {    "_avenrun"  },
    {    0           }
};

main()
{
    int kmem;
    char *ctime();
    struct timeval boottime;

    /*
     * _avenrun is an array of three numbers.
     * Most machines use floating point; Sun
     * workstations use long integers.
     */
#ifdef sun
    long avenrun[3];
#else
    double avenrun[3];
#endif

    /*
     * Open kernel memory.
     */
    if ((kmem = open("/dev/kmem", O_RDONLY)) < 0) {
        perror("/dev/kmem");
        exit(1);
    }

    /*
     * Read the kernel namelist.  If nl[0].n_type is
     * 0 after this, then the call to nlist() failed.
     */
    if ((nlist("/vmunix", nl) < 0) || (nl[0].n_type == 0)) {
        fprintf(stderr, "/vmunix: no namelist\n");
        exit(1);
    }

    /*
     * Read the _boottime variable.  We do this by
     * seeking through memory to the address found
     * by nlist, and then reading.
     */
    lseek(kmem, (long) nl[X_BOOTTIME].n_value, L_SET);
    read(kmem, (char *) &boottime, sizeof(boottime));
    /*
     * Read the load averages.
     */
    lseek(kmem, (long) nl[X_AVENRUN].n_value, L_SET);
    read(kmem, (char *) avenrun, sizeof(avenrun));

    /*
     * Now print the system boot time.
     */
    printf("System booted at %s\n", ctime(&boottime.tv_sec));

    /*
     * Print the load averages.  Sun workstations use
     * FSCALE to convert the long integers to floating
     * point.  The three elements of _avenrun are the
     * load average over the past one, five, and ten
     * minutes.
     */
#ifdef sun
    printf("One minute load average:  %.2f\n",
        (double) avenrun[0] / FSCALE);
    printf("Five minute load average: %.2f\n",
        (double) avenrun[1] / FSCALE);
    printf("Ten minute load average:  %.2f\n",
        (double) avenrun[2] / FSCALE);
#else
    printf("One minute load average:  %.2f\n", avenrun[0]);
    printf("Five minute load average: %.2f\n", avenrun[1]);
    printf("Ten minute load average:  %.2f\n", avenrun[2]);
#endif

    close(kmem);
    exit(0);
}

