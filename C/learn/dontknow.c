// this program is used to show the byte representation of different data types in C.
#include <stdio.h>

typedef unsigned char *byte_pointer; // define a type for a pointer to unsigned char

void show_bytes(byte_pointer start, size_t len) {// function to display the bytes of a given memory location
    int i;
    for (i = 0; i < len; i++) {
        printf(" %.2x", start[i]);
    }
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer) &x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer) &x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer) &x, sizeof(void *));
}