#include <stdio.h>

#define LOWER 0
#define UPPER 150
#define STEP 15

int main () {
    printf("Celsius to Fahrenheit conversion table\n");
    double celcius, fahrenheit;

    
    printf("%s\t %s\n", "celcius", "fahrenheit");
    for (celcius = LOWER; celcius <= UPPER; celcius += STEP) {
        fahrenheit = (celcius * 9 / 5) + 32;
        printf("%3.0f\t %6.1f\n", celcius, fahrenheit);
        
    }
}