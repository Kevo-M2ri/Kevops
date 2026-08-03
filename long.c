#include <stdio.h>

long mult2(long, long);

long multstore(long x, long y, long *dest) {
    long t = mult2(x, y);
    return t;
} int main() {
    long d;
    multstore(2, 3, &d);
    printf("2 * 3 --> %ld\n", d);
    return 0;
}