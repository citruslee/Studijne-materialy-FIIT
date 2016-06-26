#include <signal.h>
#include <sys/ioctl.h>
#include "10.h"

fg(j)
JOB *j;
{
    /*
     * If the terminal is not in the job's process
     * group, change the process group of the
     * terminal.
     */
    if (j->pgrp != TermPgrp) {
        ioctl(1, TIOCSPGRP, &j->pgrp);
        TermPgrp = j->pgrp;
    }

    /*
     * If the job is not running, start it up.
     */
    if (j->status & JSTOPPED) {
        killpg(j->pgrp, SIGCONT);
        j->status &= ~JSTOPPED;
        j->status |= JRUNNING;
    }

    /*
     * Go wait for the job to complete.
     */
    waitfor();
}

