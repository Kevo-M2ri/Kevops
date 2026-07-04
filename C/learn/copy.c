#include <stdio.h>

int main() {
    printf("%d", EOF);
    int c;
    while ((c = getchar()) != EOF) {
        putchar(c);
        c = getchar();
    }}