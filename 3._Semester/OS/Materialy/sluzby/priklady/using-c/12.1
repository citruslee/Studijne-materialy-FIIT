/*
 * Connects to the local host at port 1234.
 */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

#define NSTRS     3     /* no. of strings  */

/*
 * Strings we send to the server.
 */
char *strs[NSTRS] = {
    "This is the first string from the client.\n",
    "This is the second string from the client.\n",
    "This is the third string from the client.\n"
};

extern int errno;

main()
{
    char c;
    FILE *fp;
    char hostname[64];
    register int i, s;
    struct hostent *hp;
    struct sockaddr_in sin;

    /*
     * Before we can do anything, we need to know
     * our hostname.
     */
    gethostname(hostname, sizeof(hostname));

    /*
     * Next, we need to look up the network
     * address of our host.
     */
    if ((hp = gethostbyname(hostname)) == NULL) {
        fprintf(stderr, "%s: unknown host.\n", hostname);
        exit(1);
    }

    /*
     * Get a socket to work with.  This socket will
     * be in the Internet domain, and will be a
     * stream socket.
     */
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("client: socket");
        exit(1);
    }

    /*
     * Create the address we will be connecting to.
     * We use port 1234 but put it into network
     * byte order.  Also, we use bcopy (see Chapter
     * 14) to copy the network number.
     */
    sin.sin_family = AF_INET;
    sin.sin_port = htons(1234);
    bcopy(hp->h_addr, &sin.sin_addr, hp->h_length);

    /*
     * Try to connect to the address.  For this to
     * succeed, the server must already have bound
     * this address, and must have issued a listen()
     * request.
     */
    if (connect(s, &sin, sizeof(sin)) < 0) {
        perror("client: connect");
        exit(1);
    }

    /*
     * We'll use stdio for reading
     * the socket.
     */
    fp = fdopen(s, "r");

    /*
     * First we read some strings from the server
     * and print them out.
     */
    for (i = 0; i < NSTRS; i++) {
        while ((c = fgetc(fp)) != EOF) {
            putchar(c);

            if (c == '\n')
                break;
        }
    }

    /*
     * Now we send some strings to the server.
     */
    for (i = 0; i < NSTRS; i++)
        send(s, strs[i], strlen(strs[i]), 0);


    /*
     * We can simply use close() to terminate the
     * connection, since we're done with both sides.
     */
    close(s);

    exit(0);
}

