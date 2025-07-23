#include <stdio.h>
#include <math.h>

int main(void) {
    int years = 15; /* number of years money is kept in account */

    int savings = 99000; /* Initial amount */
    float interest = 1.5; /* Interest in percent */

    printf("The total savings after %d years is %.2f\n", years, savings * pow(1 + (interest / 100), years));

    return 0;
}

