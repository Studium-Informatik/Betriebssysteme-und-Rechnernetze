#include <stdio.h>

int main() {
    int a [8];
    int i;

    for (i = 0; i < sizeof(a) / sizeof(a[0]); i ++) {
        a[i] = 1;
	printf("%d\n", a[i]);
    }
}
