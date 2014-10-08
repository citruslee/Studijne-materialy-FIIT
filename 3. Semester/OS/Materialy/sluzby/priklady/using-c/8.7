#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include <stdio.h>

char *stack;      /* pointer to signal stack base */
int tooksig = 0;  /* 1 after we take the signal   */

main()
{
    extern void x();
    struct sigvec sv;
    struct sigstack ss;
    struct rlimit rlimit;

    /*
     * Set stack size limit to 50 kbytes.
     */
    getrlimit(RLIMIT_STACK, &rlimit);
    rlimit.rlim_cur = 50 * 1024;

    if (setrlimit(RLIMIT_STACK, &rlimit) < 0) {
        perror("setrlimit");
        exit(1);
    }

    /*
     * Take illegal instruction and process it with x,
     * on the interrupt stack.  For 4.2BSD, change
     * sv_flags to sv_onstack and SV_ONSTACK to 1.
     */
    sv.sv_mask = 0;
    sv.sv_handler = x;
    sv.sv_flags = SV_ONSTACK;
    sigvec(SIGILL, &sv, (struct sigvec *) 0);

    /*
     * Allocate memory for the signal stack.  The
     * kernel assumes the addresses grow in the same
     * direction as on the process stack (toward
     * lower addresses, on a VAX).
     */
    if ((stack = (char *) malloc(10240)) == NULL) {
        fprintf(stderr, "Out of memory.\n");
        exit(1);
    }

    /*
     * Issue the call to tell the system about the
     * signal stack.  We pass the end of the signal
     * stack, not the beginning, since the stack
     * grows toward lower addresses.
     */
    ss.ss_onstack = 0;
    ss.ss_sp = (caddr_t) stack + 10240;

    if (sigstack(&ss, (struct sigstack *) 0) < 0) {
        perror("sigstack");
        exit(1);
    }

    /*
     * Start using up stack space.
     */
    y();
}

y()
{
    /*
     * Take up 5k of stack space.
     */
    char buf[5120];

    printf("%s\n", tooksig ? "Now on extended stack." :
        "On 50k stack.");

    /*
     * Recurse.
     */
    y();
}

/*
 * Handle the signal.
 */
void x(sig, code, scp)
int sig, code;
struct sigcontext *scp;
{
    struct rlimit rlimit;

    /*
     * Increase the stack limit to the maximum.
     */
    getrlimit(RLIMIT_STACK, &rlimit);
    rlimit.rlim_cur = rlimit.rlim_max;

    if (setrlimit(RLIMIT_STACK, &rlimit) < 0) {
        perror("setrlimit");
        exit(1);
    }

    tooksig = 1;
    return;
}

