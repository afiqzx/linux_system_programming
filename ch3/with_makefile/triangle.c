
#include <stdio.h>

int triangle(void) {
    float height;
    float width;
    printf("Enter the height and width of the rectangle: ");
    if(scanf("%f %f", &height, &width)) {
        printf("%.3f\n", height * width / 2.0);
        return 1;
    }
    else {
        return -1;
    }
}
