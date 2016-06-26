#include <signal.h>
#include <sys/ioctl.h>
#include "10.h"

bg(j)
JOB *j;
{
    /*
     * If the job is already running,
     * there's no need to start it.
     */
    if (j->status & JRUNNING)
        return;

    /*
     * Start the job.
     */
    killpg(j->pgrp, SIGCONT);

    /*
     * Mark the job as running.
     */
    j->status &= ~JSTOPPED;
    j->status |= JRUNNING;
}

