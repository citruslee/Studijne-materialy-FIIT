#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>

main()
{
    int n, nfds;
    char buf[32];
    fd_set readfds;
    struct timeval tv;

    /*
     * We will be reading from standard input (file
     * descriptor 0), so we want to know when the
     * user has typed something.
     */
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    /*
     * Set the timeout for 15 seconds.
     */
    tv.tv_sec = 15;
    tv.tv_usec = 0;

    /*
     * Prompt for input.
     */
    printf("Type a word; if you don't in 15 ");
    printf("seconds I'll use \"WORD\": ");
    fflush(stdout);

    /*
     * Now call select.  We pass NULL for
     * writefds and exceptfds, since we
     * aren't interested in them.
     */
    nfds = select(1, &readfds, NULL, NULL, &tv);

    /*
     * Now we check the results.  If nfds is zero,
     * then we timed out, and should assume the
     * default.  Otherwise, if file descriptor 0
     * is set in readfds, that means that it is
     * ready to be read, and we can read something
     * from it.
     */
    if (nfds == 0) {
        strcpy(buf, "WORD");
    }
    else {
        if (FD_ISSET(0, &readfds)) {
            n = read(0, buf, sizeof(buf));
            buf[n-1] = '\0';
        }
    }

    printf("\nThe word is: %s\n", buf);
    exit(0);
}

