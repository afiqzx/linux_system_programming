#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

int main(void) {
    char mypass[] = "supersecret";
    char buffer[256] = { 0 };
    struct termios term;

    /* get current settings */
    tcgetattr(STDIN_FILENO, &term);
    /* disable echoing */
    term.c_lflag = term.c_lflag & ~ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);


    printf("Enter password: ");
    scanf("%s", buffer);
    if((strcmp(mypass, buffer) == 0)) {
        printf("\nCorrect password, welcome!\n");
    }
    else {
        printf("\nIncorrect password, go away!\n");
    }

    /* re-enable echoing */
    term.c_lflag = term.c_lflag | ECHO;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &term);


    return 0;
}
