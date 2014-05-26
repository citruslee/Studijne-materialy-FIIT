#include <signal.h>

main()
{
    /*
     * Declare handler routine so we can use its
     * name.
     */
    extern int handler();
    /*
     * Send signal to handler routine.  Only do so
     * if the signal is not already being ignored.
     */
    if (signal(SIGINT, SIG_IGN) != SIG_IGN)
        signal(SIGINT, handler);
    /*
     * Loop here.
     */
    for (;;)
        pause();
}
/*
 * handler--handle the signal.  sig is the signal
 *           number which interrupted us.
 */
handler(sig)
int sig;
{
    /*
     * Users of 4.2 and 4.3BSD systems should un-comment
     * this line, which will make this program
     * behave as if it were on a non-Berkeley
     * system (we reset the signal by hand).
     */
    /* signal(sig, SIG_DFL); */
    /*
     * Ignore the signal for the duration of this
     * routine.
     */
    signal(sig, SIG_IGN);
    printf("OUCH\n");
    /*
     * Reset the signal to come here again.
     */
    signal(SIGINT, handler);
}

