#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>
#include <signal.h>

void sigHandler(int sig);

const char pidfile[] = "/run/my-daemon.pid";
FILE *fp;

int main(void) {
    pid_t pid;
    time_t now;
    struct sigaction action;

    const char daemonfile[] = "/tmp/my-daemon-is-alive.txt";

    if((pid = fork()) == -1) {
        perror("Cannot fork");
        return 1;
    }
    else if((pid != 0)) {
        exit(0);
    }

    setsid();


    if((pid = fork()) == -1) {
        perror("Cannot fork");
        return 1;
    }
    else if(pid > 0) {
        if((fp = fopen(pidfile, "w")) == NULL) {
            perror("Cannot open file for writing");
            return 1;
        }

        fprintf(fp, "%d\n", pid);
        fclose(fp);
        exit(0);
    }

    umask(022); /* set the umask to something okay */
    chdir("/");

    if((fp = fopen(daemonfile, "w")) == NULL) {
        perror("Cannot open daemonfile");
        return 1;
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    /* Reopen stdin, stdout, stderr. because if this process create a file descriptor, it
     * might not get file descriptor 0,1,2. But black hole it into /dev/null */
    open("/dev/null", O_RDONLY);
    open("/dev/null", O_WRONLY);
    open("/dev/null", O_RDWR);

    action.sa_handler = sigHandler;
    sigfillset(&action.sa_mask);
    action.sa_flags = SA_RESTART;

    /* register the signals we want to handle */
    sigaction(SIGTERM, &action, NULL);
    sigaction(SIGINT, &action, NULL);
    sigaction(SIGQUIT, &action, NULL);
    sigaction(SIGABRT, &action, NULL);


    /* daemon "work" */
    for(;;) {
        time(&now);
        fprintf(fp, "Daemon alive at %s", ctime(&now));
        fflush(fp);
        sleep(30);
    }

    return 0;

}

void sigHandler(int sig) {
    int status = 0;

    if(sig == SIGTERM || sig == SIGINT || sig == SIGQUIT || sig == SIGABRT) {
        if((unlink(pidfile)) == -1 ) {
            fprintf(fp, "Failed to delete PID file\n");
            fflush(fp);
            status = 1;
        }
        if((fclose(fp)) == EOF) {
            status = 1;
        }

        exit(status);
    }
    else {
        exit(1);
    }

}
