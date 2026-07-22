//header files
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

//main function
int main(int argc, char* argv[]) {
    //declarations
    int frac_bits, exp_bits, bias;
    unsigned int hex_value, frac_mask, exp_mask, fraction, exponent, sign;
    double mant, expe, total_value;


    if (argc != 4) {//number of expected arguments
        printf("Usage: fp_parse <# of frac_bits> <# of exp_bits> <hex_to_convert>");
        return 1;
    }

    //already saved string inputs
    sscanf(argv[1], "%d", &frac_bits);
    sscanf(argv[2], "%d", &exp_bits);
    sscanf(argv[3], "%x", &hex_value);

    //validity of frac_bits and exp_bits
    if (frac_bits < 2 || frac_bits > 10) {
        printf("Illegal number of fraction bits (%d) .  Should be between 2 and 10", frac_bits);
        return 1;
    }
    if (exp_bits < 3 || exp_bits > 5) {
        printf("Illegal number of exponent bits (%d).   Should be between 3 and 5", exp_bits);
        return 1;
    }

    //splitting hex to its sign, exponent, and fraction(had an error and got help with Google)
    frac_mask = (1 << frac_bits) - 1;
    exp_mask = (1 << exp_bits) - 1;

    fraction = hex_value & frac_mask;//leave fraction bits only(most right)
    exponent = (hex_value >> frac_bits) & exp_mask;//grabbing exponents bits in
    sign = (hex_value >> (frac_bits + exp_bits)) & 1;//isolating the sign bit(most left)

    bias = (1 << (exp_bits - 1)) - 1;//(bias in the bit)

    //edge cases(infinity/NaN)
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
    else {//mantisa and exponent calculations
        if (exponent == 0) {//demormalized numbers
            expe = 1 - bias;
            mant = (double)fraction / pow(2.0, frac_bits);
        }
        else {//normalized numbers
            expe = (int)exponent - bias;
            mant = 1.0 + ((double)fraction / pow(2.0, frac_bits));
        }
        //putting the pieces back together
        total_value = mant * pow(2.0, expe);
        if (sign) {
            total_value = -total_value;
        }
        printf("%f\n", total_value);
    }
}


