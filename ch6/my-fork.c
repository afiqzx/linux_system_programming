#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid;
    int status;

    printf("My PID is %d\n", getpid());
    getchar();
    if((pid = fork()) == -1) {
        perror("Cannot fork");
        return 1;
    }

    /* child process */
    if(pid == 0) {
        if(execl("/usr/bin/man", "man", "ls", NULL) == -1) {
            perror("Cannot run man");
            return 1;
        }
    }
    else if(pid > 0) {
        waitpid(pid, &status, 0);
        printf("Child executed with PID %d\n", pid);
        printf("Its return status was %d\n", status);
    }
    else {
        perror("Something went really wrong");
        return 1;
    }

    return 0;
}
