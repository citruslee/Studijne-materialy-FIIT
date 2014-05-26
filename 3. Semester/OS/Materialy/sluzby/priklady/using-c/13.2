/*
 * Reads the i-node structures from a raw disk device and 
 * then sums up the disk usage for each user.  Prints out 
 * the number of blocks each user is using.
 *
 * If you are on a Sun workstation or other system using Sun's
 * Network File System (NFS), be sure to define the constant
 * NFS so that the proper files get included.
 */
#ifdef sun
#define NFS     1
#endif
#ifdef NFS
#include <sys/param.h>
#include <sys/time.h>
#include <sys/vnode.h>
#include <ufs/inode.h>
#include <sys/file.h>
#include <ufs/fs.h>
#include <stdio.h>
#include <pwd.h>
#else
#include <sys/param.h>
#include <sys/inode.h>
#include <sys/file.h>
#include <sys/fs.h>
#include <stdio.h>
#include <pwd.h>
#endif
/*
 * Maximum user id.
 */
#ifndef MAXUID
#define MAXUID  32768
#endif

#define sblock    sb_un.u_sblock

/*
 * The super block.  We allow enough room for
 * a complete disk block.
 */
union {
    struct  fs u_sblock;
    char    dummy[SBSIZE];
} sb_un;

int nfiles;            /* number of files in file system      */

char    *pname;        /* program name (argv[0])              */
char    *device;       /* name of the disk device given       */
char    *filsys;       /* name of the file system on device   */

size_t blocks[MAXUID]; /* count of blocks used                */
struct dinode *dinode; /* will hold all the i-node structures */

main(argc, argv)
int argc;
char **argv;
{
    int i, fd;
    register ino_t ino;
    register struct dinode *di;

    /*
     * Save the program name and check our arguments.
     */
    pname = *argv;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s raw-disk-device\n", pname);
        exit(1);
    }

    /*
     * Open the device for reading.
     */
    device = *++argv;

    if ((fd = open(device, O_RDONLY)) < 0) {
        perror(device);
        exit(1);
    }

    /*
     * Get the super-block from the device.
     */
    getsblock(fd);

    /*
     * Get the i-node structures from the device.
     */
    getinodes(fd);
    close(fd);

    /*
     * Zero the block counts.
     */
    for (i = 0; i < MAXUID; i++)
        blocks[i] = 0;

    /*
     * Add up the number of blocks being used by
     * each user id.
     */
    for (ino = 0; ino < nfiles; ino++) {
        /*
         * ROOTINO is the first i-node; skip any
         * before it.
         */
        if (ino < ROOTINO)
            continue;

        di = &dinode[ino];

        /*
         * If this is zero, the i-node is free (not
         * in use).
         */
        if ((di->di_mode & IFMT) == 0)
            continue;

        /*
         * Count the number of blocks being used by
         * this file.
         */
        blocks[di->di_uid] += di->di_blocks;
    }

    /*
     * Print out what we added up.
     */
    printusage();
    exit(0);
}

/*
 * getsblock--get the super-block from the device
 *             referred to by fd.
 */
getsblock(fd)
int fd;
{
    /*
     * Make sure the disk information is current.
     * This causes all disk writes to be scheduled.
     */
    sync();

    /*
     * Read in the super-block.  It is stored at file
     * system block number SBLOCK.
     */
    bread(fd, SBLOCK, &sblock, SBSIZE);

    /*
     * The number of files (i-nodes) is calculated by
     * multiplying the number of i-nodes per cylinder
     * group by the number of cylinder groups.
     */
    nfiles = sblock.fs_ipg * sblock.fs_ncg;

    /*
     * Save the name of the file system.
     */
    filsys = sblock.fs_fsmnt;
}

/*
 * getinodes--read in the i-node structures from the device
 *             referred to by fd.
 */
getinodes(fd)
int fd;
{
    register ino_t ino;
    register daddr_t iblk;
    struct dinode *malloc();

    /*
     * Allocate space for them all.
     */
    dinode = malloc(nfiles * sizeof(struct dinode));

    if (dinode == NULL) {
        fprintf(stderr, "%s: out of memory.\n", pname);
        exit(1);
    }

    /*
     * We read in i-nodes a disk block-full at a time.
     * The INOPB macro returns the number of i-nodes
     * in a block; it uses the super-block to determine
     * the file system block size.
     */
     for (ino = 0; ino < nfiles; ino += INOPB(&sblock)) {
     /*
      * The i-node file system block number is given by 
      * the itod macro.  The disk block number is computed
      * from the file system block number by the fsbtodb macro.
      */

       iblk = fsbtodb(&sblock, itod(&sblock, ino));

       /*
        * Read in this block of i-nodes.
        */
       bread(fd, iblk, &dinode[ino], sblock.fs_bsize);
    }
}
 
/*
 * bread-read cnt bytes form fd into buf, starting at
 *          address bno.
 */
bread(fd, bno, buf, cnt)
daddr_t bno;
char *buf;
int cnt;
{
    int n;

    /*
     * Seek to the proper block.  The dtob macro converts 
     * the block number to a byte address.
     */
    lseek(fd, (long) dtob(bno), L_SET);

    /* 
     * Round cnt up to a multiple of the device block size.
     */
    cnt = roundup(cnt, DEV_BSIZE);

    /*
     * Read in the data.
     */
    if ((n = read(fd, buf, cnt)) != cnt) {
       perror(filsys);
       exit(1);
    }
}

/*
 * printusage-print out the disk usage in blocks.
 */
printusage()
{
    register int i;
    struct passwd *pwd;

    printf("%s (%s):\n", device, filsys);
    printf(" Blocks \\t  User\n");

    for (i=0; i < MAXUID; i++) {
          if (blocks[i] == 0)
              continue;

      /*
       * Look up the login name, and use it if we find it.
       */
      if ((pwd = getpwuid(i)) != NULL)
         printf("%8d\\t%s\n", blocks[i], pwd->pw_name);
      else
         printf("%8d\\t#%d\n", blocks[i], i);
    }
}

