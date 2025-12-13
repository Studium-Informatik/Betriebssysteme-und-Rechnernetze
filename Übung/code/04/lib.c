
#include <stdio.h>
#include <sys/time.h>

#define ITERATIONS 10000000

int main(void) {
    struct timeval tv;

    for (int i = 0; i < ITERATIONS; i++) {
        gettimeofday(&tv, NULL);
    }

    return 0;
}
