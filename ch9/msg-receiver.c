#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>

int main(void) {
    int md;
    char *buffer;
    struct mq_attr msgattr;

    md = mq_open("/my_queue", O_RDONLY);
    if(md == -1) {
        perror("Open message queue failed");
        return 1;
    }

    if((mq_getattr(md, &msgattr)) == -1) {
        perror("Failed to get message attribute");
        return 1;
    }

    buffer = calloc(msgattr.mq_msgsize, sizeof(char));
    if(buffer == NULL) {
        perror("Failed to malloc");
        return 1;
    }

    printf("%ld message in queue\n", msgattr.mq_curmsgs);
    for(int i = 0; i < msgattr.mq_curmsgs; i++) {
        if((mq_receive(md, buffer, msgattr.mq_msgsize, NULL)) == -1) {
            perror("Failed to receive message");
            return 1;
        }

        printf("%s\n", buffer);
        memset(buffer, 0, msgattr.mq_msgsize);
    }

    free(buffer);
    mq_close(md);

    mq_unlink("/my_queue");


    return 0;
}
