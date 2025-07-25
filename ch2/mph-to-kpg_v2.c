#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

void printHelp(FILE *, const char []);


int main(int argc, const char *argv[]) {
    char mph[10] = { 0 };
    int opt;
    int cont = 0;

    /* Parse command-line options */
    while((opt = getopt(argc, (char * const*)argv, "ch")) != -1) {
        switch(opt) {
            case 'h':
                printHelp(stdout, argv[0]);
                return 0;
            case 'c':
                cont = 1;
                break;
            default:
                printHelp(stderr, argv[0]);
                return 1;
        }
    }

    while(fgets(mph, sizeof(mph), stdin) != NULL) {
        /* Check if mph is numeric
         * (and do conversion) */
        if(strspn(mph, "0123456789.-\n") == strlen(mph)) {
            printf("%.1f\n", (atof(mph) * 1.60934));
        }
        else {
            fprintf(stderr, "Found non-numeric value\n");


            /* check continuation flag */
            if(cont == 1) {
                continue;
            }
            else {
                return 1;
            }
        }

    }


    return 0;
}

void printHelp(FILE * stream, const char progname[]) {
    fprintf(stream, "%s [-c] [-h]\n", progname);
    fprintf(stream, " -c continues even though a non"
    "-numeric value was detected in the input\n"
    " -h print help\n");
}
