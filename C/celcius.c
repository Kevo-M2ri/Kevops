#include <stdio.h>

int main () {
    printf("Celsius to Fahrenheit conversion table\n");
    double celcius, fahrenheit;
    double lower, upper, step;

    lower = 0;
    upper = 150;
    step = 15;

    celcius = lower;
    printf("%s\t %s\n", "celcius", "fahrenheit");
    while (celcius <= upper) {
        fahrenheit = (celcius * 9 / 5) + 32;
        printf("%3.0f\t %6.1f\n", celcius, fahrenheit);
        celcius = celcius + step;
    }
}