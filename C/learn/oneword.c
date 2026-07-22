#include <stdio.h>

int main() {
    char c;
    while ((c = getchar()) != EOF) {
        if (c == '\n' || c == ' ' || c == '\t') {
            putchar('\n');
        }
        else {
            putchar(c);
        }
    }
}