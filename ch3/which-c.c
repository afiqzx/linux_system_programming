#include <stdio.h>

int main(void) {

#ifdef __STDC_VERSION__
    printf("Standard C version: %ld\n", __STDC_VERSION__);
#endif

#ifdef _XOPEN_SOURCE
    printf("_XOPEN_SOURCE: %d\n", _XOPEN_SOURCE);
#endif
#ifdef _GNU_SOURCE
    printf("_GNU_SOURCE: %d\n", _GNU_SOURCE);
#endif
#ifdef _BSD_SOURCE
    printf("_BSD_SOURCE: %d\n", _BSD_SOURCE);
#endif
#ifdef _DEFAULT_SOURCE
    printf("_DEFAULT_SOURCE: %d\n", _DEFAULT_SOURCE);
#endif

    return 0;
}
