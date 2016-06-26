#include <sys/time.h>
#include <signal.h>

#define setvec(vec, a) \
            vec.sv_handler = a; \
            vec.sv_mask = vec.sv_flags = 0

static int ringring;

nap(n)
unsigned n;
{
    void napx();
    int omask;
    struct sigvec vec, ovec;
    struct itimerval itv, oitv;
    register struct itimerval *itp = &itv;

    if (n == 0)
        return;
    timerclear(&itp->it_interval);
    timerclear(&itp->it_value);
    if (setitimer(ITIMER_REAL, itp, &oitv) < 0)
        return;
    setvec(ovec, SIG_DFL);
    omask = sigblock(sigmask(SIGALRM));
    itp->it_value.tv_sec = n/60;
    itp->it_value.tv_usec = (n%60)*1000000/60;
    if (timerisset(&oitv.it_value)) {
        if (oitv.it_value.tv_sec >= itp->it_value.tv_sec) {
            if (oitv.it_value.tv_sec == itp->it_value.tv_sec &&
                oitv.it_value.tv_usec > itp->it_value.tv_usec)
                oitv.it_value.tv_usec -= itp->it_value.tv_usec;
                    oitv.it_value.tv_sec -= itp->it_value.tv_sec;
        }
        else {
            itp->it_value = oitv.it_value;
            /*
             * This is a hack, but we must have time to return from 
             * the setitimer after the alarm or else it will restart.
             * And, anyway, sleep never did more than this before.
             */
            oitv.it_value.tv_sec = 1;
            oitv.it_value.tv_usec = 0;
        }
    }
    setvec(vec, napx);
    ringring = 0;
    sigvec(SIGALRM, &vec, &ovec);
    setitimer(ITIMER_REAL, itp, (struct itimerval *)0);
    while (!ringring)
        sigpause(omask &~ sigmask(SIGALRM));
    sigvec(SIGALRM, &ovec, (struct sigvec *)0);
    setitimer(ITIMER_REAL, &oitv, (struct itimerval *)0);
    sigsetmask(omask);
}

static void
napx()
{
    ringring = 1;
}

