

#include <stdio.h>
#include <unistd.h>


int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s [target] [link]\n", argv[0]);
        return 1;
    }

    if(symlink(argv[1], argv[2]) == -1) {
        perror("Can't create link");
    }

    return 0;
}
