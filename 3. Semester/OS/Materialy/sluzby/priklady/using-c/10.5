#include <sys/wait.h>
#include <sys/signal.h>
#include <sys/ioctl.h>
#include "10.h"

waitfor()
{
    int pid;
    JOB *j;
    PROC *p;
    JOB *findjob();
    union wait status;

    /*
     * As long as we get something's status back...
     */
    while ((pid = wait3(&status, WUNTRACED, 0)) >= 0) {
        /*
         * Find the job structure which has this
         * process.
         */
        j = findjob(pid);

        /*
         * Find the process structure.
         */
        for (p = j->procs; p->pid != pid; p = p->next)
            /* empty */ ;

        /*
         * Find out what happened to the process.
         */
        if (WIFSTOPPED(status)) {
            /*
             * See if we know the reason it was
             * stopped. The w_stopsig element of
             * the structure contains the number
             * of the signal which stopped the
             * process.
             */
            switch (status.w_stopsig) {
            case SIGTTIN:
                p->status |= PTTYINPUT;
                break;
            case SIGTTOU:
                p->status |= PTTYOUTPUT;
                break;
            case SIGSTOP:
                p->status |= PSTOPSIGNAL;
                break;
            default:
                break;
            }

            p->status |= PSTOPPED;
            j->status |= JNEEDNOTE;
        }
        else if (WIFEXITED(status)) {
            /*
             * Normal termination.
             */
            if (status.w_retcode == 0)
                p->status |= PDONE;
            else
                p->status |= PEXITED;

            p->exitcode = status.w_retcode;

            /*
             * We're only going to note processes
             * exiting if all the processes in the
             * job are complete.
             */
            if (alldone(j))
                j->status |= JNEEDNOTE;
        }
        else if (WIFSIGNALED(status)) {
            p->status |= PSIGNALED;

            /*
             * Save the termination signal.
             */
            p->termsig = status.w_termsig;

            /*
             * Check for a core dump.
             */
            if (status.w_coredump)
                p->status |= PCOREDUMP;

            /*
             * We're only going to note processes
             * exiting if all the processes in the
             * job are complete.
             */
            if (alldone(j))
                j->status |= JNEEDNOTE;
        }

        /*
         * If this process is the one which was in the
         * foreground, we need to do special things,
         * and then return to the main control section
         * of the shell.
         */
        if (j->pgrp == TermPgrp) {
            /*
             * If the job is stopped, we need to call
             * the stop routine.
             */
            if (WIFSTOPPED(status)) {
                stop(j);
                printf("Stopped\n");
            }

            /*
             * If the job exited or died somehow, we
             * need to regain control of the terminal.
             */
            if (WIFEXITED(status) || WIFSIGNALED(status)) {
                ioctl(1, TIOCSPGRP, &MyPgrp);
                TermPgrp = MyPgrp;
            }

            /*
             * Go back.
             */
            return;
        }
    }
}

