/*
 * mailer - open a pipe to the mail command and send the user
 *          mail.
 */
#include <stdio.h>

main()
{
    FILE *fp;
    int pid, pipefds[2];
    char *username, *getlogin();

    /*
     * Get the user's name.
     */
    if ((username = getlogin()) == NULL) {
        fprintf(stderr, "Who are you?\n");
        exit(1);
    }

    /*
     * Create the pipe.  This has to be done
     * BEFORE the fork.
     */
    if (pipe(pipefds) < 0) {
        perror("pipe");
        exit(1);
    }

    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    /*
     * The child process executes the stuff inside
     * the if.
     */
    if (pid == 0) {
        /*
         * Make the read side of the pipe our
         * standard input.
         */
        close(0);
        dup(pipefds[0]);
        close(pipefds[0]);

        /*
         * Close the write side of the pipe;
         * we'll let our output go to the screen.
         */
        close(pipefds[1]);

        /*
         * Execute the command "mail username".
         */
        execl("/bin/mail", "mail", username, 0);
        perror("exec");
        exit(1);
    }

    /*
     * The parent executes this code.
     */

    /*
     * Close the read side of the pipe; we
     * don't need it (and the child is not
     * writing on the pipe anyway).
     */
    close(pipefds[0]);

    /*
     * Convert the write side of the pipe to stdio.
     */
    fp = fdopen(pipefds[1], "w");

    /*
     * Send a message, close the pipe.
     */
    fprintf(fp, "Hello from your program.\n");
    fclose(fp);

    /*
     * Wait for the process to terminate.
     */     
    while (wait((int *) 0) != pid)
        ;

    exit(0);
}
