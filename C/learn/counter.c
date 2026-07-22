#include <stdio.h>

int main() {
    char xc, last_space;
    while ((xc = getchar()) != EOF) {
        if (xc == '\t') {
            xc = ' ';
        }

        if (xc == ' ') {
            if (!last_space) {
                putchar(xc);
                last_space = 1;
            }
            else {
                putchar(xc);
                last_space = 0;
            }
        }
    }
    printf("%c", xc);
}