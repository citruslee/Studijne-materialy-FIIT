#include <sys/ioctl.h>
#include "10.h"

int MyPid;        /* the shell's process id       */
int MyPgrp;       /* the shell's process group    */
int TermPgrp;     /* the terminal's process group */

setup()
{
    /*
     * Obtain shell's process id.
     */
    MyPid = getpid();

    /*
     * Just use pid for process group.  This is
     * not a requirement, just convenient.  Other
     * ways of picking a process group can be used.
     */
    MyPgrp = MyPid;
    TermPgrp = MyPid;

    /*
     * Set the shell's process group.
     */
    if (setpgrp(MyPid, MyPgrp) < 0) {
        perror("setpgrp");
        exit(1);
    }

    /*
     * Set the terminal's process group.
     */
    if (ioctl(1, TIOCSPGRP, &MyPgrp) < 0) {
        perror("ioctl");
        exit(1);
    }
}

