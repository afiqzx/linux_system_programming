#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>


void cleanUp(int signum);
int fifo_fd;

const char fifoname[] = "/tmp/my-2nd-fifo";

int main(int argc, char *argv[]) {
    struct sigaction action;

    if(argc != 2) {
        fprintf(stderr, "Usage: %s 'the message'\n", argv[0]);
        return 1;
    }

    /* prepare for sigaction and register signals
     * for cleanup when we exit */
    action.sa_handler = cleanUp;
    sigfillset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
    sigaction(SIGABRT, &action, NULL);
    sigaction(SIGPIPE, &action, NULL);
     
    if((mkfifo(fifoname, 0644)) != 0) {
        perror("Can't create FIFO");
        return 1;
    }

    if((fifo_fd = open(fifoname, O_WRONLY)) == -1) {
        perror("Can't open FIFO");
        return 1;
    }

    while(1) {
        dprintf(fifo_fd, "%s\n", argv[1]);
        sleep(1);
    }

    close(fifo_fd);
    unlink(fifoname);


    return 0;
}

void cleanUp(int signum) {
    if(signum == SIGPIPE)
        printf("The receiver stopped receiving\n");
    else
        printf("Aborting...\n");

    if((close(fifo_fd)) == -1)
        perror("Cannot close file descriptor");

    if((unlink(fifoname)) == -1) {
        perror("Cannot remove FIFO");
        exit(1);
    }

    exit(0);

}


