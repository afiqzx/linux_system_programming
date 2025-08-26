#include <stdio.h>
#include <stdlib.h>

int main(void) {
    if((system("man ls")) == -1) {
        perror("Error forking or reading status");
        return 1;
    }
    return 0;
}
