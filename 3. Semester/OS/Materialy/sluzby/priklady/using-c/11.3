#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>

#define MSGSZ     128

#ifdef	NOT_USED
/*
 * Declare the message structure.
 */
struct msgbuf {
    long    mtype;
    char    mtext[MSGSZ];
};
#endif	/* NOT_USED */

main()
{
    int msqid;
    key_t key;
    struct msgbuf sbuf, rbuf;

    /*
     * Create a message queue with "name" 1234.
     */
    key = 1234;

    /*
     * We want to let everyone read and
     * write on this message queue, hence
     * we use 0666 as the permissions.
     */
    if ((msqid = msgget(key, IPC_CREAT | 0666)) < 0) {
        perror("msgget");
        exit(1);
    }

    /*
     * Receive a message.
     */
    if (msgrcv(msqid, &rbuf, MSGSZ, 0, 0) < 0) {
        perror("msgrcv");
        exit(1);
    }

    /*
     * We send a message of type 2.
     */
    sbuf.mtype = 2;
    sprintf(sbuf.mtext, "I received your message.");

    /*
     * Send an answer.
     */
    if (msgsnd(msqid, &sbuf, strlen(sbuf.mtext) + 1, 0) < 0) {
        perror("msgsnd");
        exit(1);
    }

    exit(0);
}

