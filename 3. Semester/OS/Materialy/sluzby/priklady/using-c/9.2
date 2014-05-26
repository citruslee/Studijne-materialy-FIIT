execute(args, sin, sout, serr)
char **args;
int sin, sout, serr;
{
    int pid, status;

    /*
     * Get a child process.
     */
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }

    /*
     * The child executes the code inside the if.
     */
    if (pid == 0) {
        /*
         * For each of standard input, output,
         * and error output, set the child's
         * to the passed-down file descriptor.
         * Note that we can't just close 0, 1,
         * and 2 since we might need them.
         */
        if (sin != 0) {
            close(0);
            dup(sin);    /* will give us fd #0 */
        }

        if (sout != 1) {
            close(1);
            dup(sout);    /* will give us fd #1 */
        }

        if (serr != 2) {
            close(2);
            dup(serr);    /* will give us fd #2 */
        }

        execvp(*args, args);
        perror(*args);
        exit(1);
    }

    /*
     * The parent executes the wait.
     */
    while (wait(&status) != pid)
        /* empty loop */;
}

