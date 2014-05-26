#include <sys/param.h>
#include <sys/ioctl.h>
#include <sys/file.h>
#include <signal.h>
#include <stdio.h>

ptyopen(cmd, ifp, ofp)
char *cmd;
FILE **ifp, **ofp;
{
    int i;
    char *args[16];
    register int tty;
    long ldisc, lmode;
    register char *s, *t;
    struct sgttyb sgttyb;
    struct tchars tchars;
    struct ltchars ltchars;
    char ttybuf[16], ptybuf[16];

    /*
     * Split up the arguments in the command
     * into an argv-like structure.
     */
    i = 0;
    s = cmd;

    while (*s) {
        /*
         * Skip white space.
         */
        while ((*s == ' ') || (*s == '\t'))
            *s++ = NULL;

        args[i++] = s;

        /*
         * Skip over this word to next white space.
         */
        while ((*s != NULL) && (*s != ' ') && (*s != '\t'))
            s++;
    }
    args[i] = NULL;
    /*
     * Get a pseudo-tty.  We do this by cycling through all 
     * the possible names.  The operating system will not 
     * allow us to open a master which is already in use,
     * so we simply go until the open succeeds.
     */
    for (s = "pqrs"; *s != NULL; s++) {
        for (t = "0123456789abcdef"; *t != NULL; t++) {
            sprintf(ptybuf, "/dev/pty%c%c", *s, *t);
            if ((tty = open(ptybuf, O_RDWR)) >= 0)
                goto out;
        }
    }
out:
    /*
     * If s and t are NULL, we ran out of pseudo ttys 
     * before we found one we can use.
     */
    if ((*s == NULL) && (*t == NULL))
        return(-1);
    /*
     * Change "ptyXX" (master) to "ttyXX" (slave).
     */
    strcpy(ttybuf, ptybuf);
    ttybuf[5] = 't';
    /*
     * Get the modes of the current terminal.  We
     * will duplicate these on the pseudo terminal.
     */
    ioctl(0, TIOCGETD, &ldisc);
    ioctl(0, TIOCLGET, &lmode);
    ioctl(0, TIOCGETP, &sgttyb);
    ioctl(0, TIOCGETC, &tchars);
    ioctl(0, TIOCGLTC, &ltchars);
    /*
     * Fork a child process.
     */
    if ((i = fork()) < 0) {
        close(tty);
        return(-1);
    }

    /*
     * In the child...
     */
    if (i == 0) {
        /*
         * Close all open files.
         */
        for (i = 0; i < NOFILE; i++)
            close(i);

        /*
         * Clear the controlling tty.  This means
         * that we will not have a controlling
         * tty until we open another terminal
         * device.
         */
        if ((i = open("/dev/tty", O_RDWR)) >= 0) {
            ioctl(i, TIOCNOTTY, 0);
            close(i);
        }

        /*
         * Make our controlling tty the pseudo tty.
         * This happens because we cleared our
         * original controlling terminal above.
         */
        i = open(ttybuf, O_RDWR);

        /*
         * Set stdin, stdout, and stderr to be the
         * pseudo terminal.
         */
        dup2(i, 0);
        dup2(i, 1);
        dup2(i, 2);

        /*
         * Set the pseudo terminal's tty modes to
         * those of the original terminal.  We
         * turn off ECHO and CBREAK modes, since
         * we don't want characters "typed" to be
         * printed.
         */
        sgttyb.sg_flags &= ~ECHO;
        sgttyb.sg_flags &= ~CRMOD;

        ioctl(0, TIOCSETD, &ldisc);
        ioctl(0, TIOCLGET, &lmode);
        ioctl(0, TIOCSETP, &sgttyb);
        ioctl(0, TIOCSETC, &tchars);
        ioctl(0, TIOCSLTC, &ltchars);

        /*
         * Set the process group of the process
         * to be the process group of the
         * terminal.
         */
        ioctl(0, TIOCGPGRP, &i);
        setpgrp(0, i);

        /*
         * Now change the process group of the
         * terminal and process to be the
         * process id; this takes them out
         * of the calling process's process
         * group.
         */
        i = getpid();

        ioctl(0, TIOCSPGRP, &i);
        setpgrp(0, i);

        /*
         * Execute the program.
         */
        execv(*args, args);

        exit(1);
    }

    /*
     * Set up the input and output file pointers
     * so that they can write and read the pseudo
     * terminal.
     */
    *ifp = fdopen(tty, "w");
    *ofp = fdopen(tty, "r");

    return(0);
}

