
#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/syscall.h>

#define ITERATIONS 10000000

int main(void) {
    struct timeval tv;

    for (int i = 0; i < ITERATIONS; i++) {
        syscall(SYS_gettimeofday, &tv, NULL);
    }

    return 0;
}
