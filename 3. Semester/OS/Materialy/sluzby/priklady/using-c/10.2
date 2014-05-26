#include <signal.h>
#include <sys/ioctl.h>
#include "10.h"

stop(j)
JOB *j;
{
    /*
     * If the job is already stopped, we don't
     * need to do anything.
     */
    if (j->status & JSTOPPED)
        return;

    /*
     * If the job's process group is not that of the
     * terminal, then the job is in the background
     * and must be sent a stop signal.
     */
    if (j->pgrp != TermPgrp)
        killpg(j->pgrp, SIGSTOP);

    /*
     * Mark the job as stopped.
     */
    j->status |= JSTOPPED;

    /*
     * If the terminal is not in the shell's process
     * group, we need to put it there.
     */
    if (TermPgrp != MyPgrp) {
        ioctl(1, TIOCSPGRP, &MyPgrp);
        TermPgrp = MyPgrp;
    }
}

