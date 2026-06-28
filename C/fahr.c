#include <stdio.h>

int main() {

    printf("Fahrenheit to Celsius conversion table\n");
    double fahr, celsius;
    double lower, upper, step;

    lower = 0; //lower limit of temperature table
    upper = 300; //upper limit
    step = 20; //step size

    fahr = lower;
    printf("%s\t %s\n", "celsius", "s");
    while (fahr <= upper) {
        celsius = 5 * (fahr - 32) / 9;
        printf("%3.0f\t %6.1f\n", fahr, celsius);
        fahr = fahr + step;
    }
}