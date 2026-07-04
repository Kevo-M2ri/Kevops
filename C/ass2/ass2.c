#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char *argv[]) {
    //declarations
    int frac_bits, exp_bits;
    unsigned int hex_value;
    unsigned int frac_mask;
    unsigned int exp_mask;
    unsigned int frac;
    unsigned exp;
    unsigned int sign;
    int bias;

    //checking for number of arguments
    if (argc != 4) {
        printf("Usage: fp_parse <# frac_bits> <# of exp_bits> hex_to_convert\n");
        return 1;
    }

    //reading input from preexisting buffer
    sscanf(argv[1], "%d", &frac_bits); // realized this from stack overflow
    sscanf(argv[2], "%d", &exp_bits);

    //checking for valid number of fraction bits
    if (frac_bits < 2 || frac_bits > 10) {
        printf("Illegal number of fraction bits (11). Should be between 2 and 10");
        return 1;
    }

    //checking for valid number of exponent bits
    if (exp_bits < 3 || exp_bits > 5) {
        printf("Illegal number of expenent bits(8). Should be between 3 and 5");
        return 1;
    }



}