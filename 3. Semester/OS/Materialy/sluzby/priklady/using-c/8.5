#include <signal.h>
#include <setjmp.h>

/*
 * The environment for setjmp.
 */
jmp_buf env;

main()
{
    int i;
    char buf[16];
    extern int timeout();

    /*
     * Inform the system we want to catch the
     * alarm signal.
     */
    signal(SIGALRM, timeout);

    /*
     * The code inside the if gets executed the first
     * time through setjmp, the code inside the else
     * the second time.
     */
    if (setjmp(env) == 0) {
        /*
         * Issue a request for an alarm to be
         * delivered in 15 seconds.
         */
        alarm(15);

        /*
         * Prompt for input.
         */
        printf("Type a word; if you don't in 15 ");
        printf("seconds I'll use \"WORD\": ");
        gets(buf);

        /*
         * Turn off the alarm.
         */
        alarm(0);
    }
    else {
        /*
         * Assume the default.
         */
        strcpy(buf, "WORD");
    }

    printf("\nThe word is: %s\n", buf);
    exit(0);
}

/*
 * timeout--catch the signal.
 */
timeout(sig)
int sig;
{
    /*
     * Ignore the signal for the duration of this
     * routine.
     */
    signal(sig, SIG_IGN);

    /*
     * We would perform any timeout-related
     * functions here; in this case there
     * are none.
     */

    /*
     * Restore the action of the alarm signal.
     */
    signal(SIGALRM, timeout);

    /*
     * Return to the main routine at setjmp,
     * and make setjmp return 1.
     */
    longjmp(env, 1);
}

