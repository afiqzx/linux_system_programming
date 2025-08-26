#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>


int main(void) {
    printf("My PID is %d\n", getpid());
    printf("Hit enter to conginue ");
    getchar();

    printf("Executing /usr/bin/less ...\n");

    if(execl("/usr/bin/less", "less", "/etc/passwd", (char*) NULL) == -1) {
        perror("Cannot execute less");
        return 1;
    }

    return 0;
}
