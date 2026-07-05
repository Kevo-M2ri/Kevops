#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
        //declarations
        int frac_bits, exp_bits, bias;
        unsigned int hex_value, frac_mask, exp_mask, fraction, exponent, sign;
        double men, ele, total_value;

    if (argc != 4) {
        printf("Usage: fp_parse <# of frac_bits> <# of exp_bits> <hex_to_convert>");
        return 1;
    }

    sscanf(argv[1], "%d", &frac_bits);
    sscanf(argv[2], "%d", &exp_bits);
    sscanf(argv[3], "%x", &hex_value);

    if (frac_bits < 2 || frac_bits > 10) {
        printf("Illegal number of fraction bits (%d) .  Should be between 2 and 10", frac_bits);
        return 1;
    }
    if (exp_bits < 3 || exp_bits > 5) {
        printf("Illegal number of exponent bits (%d).   Should be between 3 and 5", exp_bits);
        return 1;
    }

    frac_mask = (1 << frac_bits) - 1;
    exp_mask = (1 << exp_bits) - 1;

    fraction = hex_value & frac_mask;
    exponent = (hex_value >> frac_bits) & exp_mask;
    sign = (hex_value >> (frac_bits + exp_bits)) & 1;

    bias = (1 << (exp_bits - 1)) - 1;

    if (exponent == exp_mask) {
        if (fraction == 0) {
            if (sign) {
                printf("-inf\n");
            }
            else {
                printf("+inf\n");
            }
        }
        else {
            printf("NaN\n");
        }
    }
    else {
        if (exponent == 0) {
            ele = 1 - bias;
            men = (double)fraction / pow(2.0, frac_bits);
        }
        else {
            ele = (int)exponent - bias;
            men = 1.0 + ((double)fraction / pow(2.0, frac_bits));
        }
        total_value = men * pow(2.0, ele);
        if (sign) {
            total_value = -total_value;
        }
        printf("%f\n", total_value);
    }
}
