#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>

#define BUFSZ       256
#define SERVICE     "daytime"

main(argc, argv)
int argc;
char **argv;
{
    int s, n, len;
    char buf[BUFSZ];
    struct hostent *hp;
    struct servent *sp;
    struct sockaddr_in sin;

    /*
     * Get a datagram socket in the Internet
     * domain.
     */
    if ((s = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }

    /*
     * Look up the port number of the service.
     */
    if ((sp = getservbyname(SERVICE, "udp")) == NULL) {
        fprintf(stderr, "%s/udp: unknown service.\n", SERVICE);
        exit(1);
    }

    /*
     * For each host on the command line...
     */
    while (--argc) {
        /*
         * Look up the network number of
         * the host.
         */
        if ((hp = gethostbyname(*++argv)) == NULL) {
            fprintf(stderr, "%s: host unknown.\n", *argv);
            continue;
        }

        /*
         * Build the address of the server on
         * the remote machine.
         */
        sin.sin_family = AF_INET;
        sin.sin_port = sp->s_port;
        bcopy(hp->h_addr, &sin.sin_addr, hp->h_length);

        /*
         * Print the name of the host.
         */
        printf("%s: ", *argv);
        fflush(stdout);

        /*
         * Send a datagram to the server.
         */
        if (sendto(s, buf, BUFSZ, 0, &sin, sizeof(sin)) < 0) {
            perror("sendto");
            continue;
        }

        /*
         * Receive a datagram back.
         */
        len = sizeof(sin);
        n = recvfrom(s, buf, sizeof(buf), 0, &sin, &len);

        if (n < 0) {
            perror("recvfrom");
            continue;
        }

        /*
         * Print the datagram.
         */
        buf[n] = NULL;
        printf("%s\n", buf);
    }

    close(s);
    exit(0);
}

