#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    printf("My username is %s\n", getenv("USER"));
    printf("Home directory is %s\n", getenv("HOME"));
    printf("Preferred editor is %s\n", getenv("EDITOR"));
    printf("Shell is %s\n", getenv("SHELL"));

    /* Check if current terminal support colors */
    if(strstr(getenv("TERM"), "256color")) {
        printf("\033[0;31mYour \033[0;32mterminal \033[0;35msupport \033[0;33mcolors\033[0m\n");
    }
    else {
        printf("Your terminal doesn't support colors\n");
    }

    return 0;
}
