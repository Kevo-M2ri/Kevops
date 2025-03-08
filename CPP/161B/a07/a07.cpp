/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        March 9, 2025
   Assignment:  CS-161B Assignment a07
   Description: This program manipulates two numbers using functions.
                It swaps the numbers, divides the first number by the second,
                and raises the first number to the power of the second.
   Inputs:      Two integers from the user.
   Outputs:     The manipulated numbers after each operation.
   -------------------------------------------------------------------------**/

#include <iostream>
using namespace std;

// Function prototypes
void swapArgs(int *a, int *b);
void divideArgs(int *a, int *b);
void powerArgs(int *a, int *b);

// Main function
int main() {
    // Variable declarations
    int a, b;
    
    cout << "Welcome to the program!" << endl << endl; // Welcome message

    cout << "Input the first number: ";// Prompt for first number
    cin >> a; //Input first number
    cout << "Input the second number: ";// Prompt for second number
    cin >> b;// Input second number

    cout << "Before any manipulation, the numbers are: " << a << " and " << b << endl;// display the numbers

    while (b > 0) {
        swapArgs(&a, &b);// Swap the numbers
        cout << "After swapping, the numbers are: " << a << " and " << b << endl;
        divideArgs(&a, &b);// Divide the numbers
        cout << "After dividing, the numbers are: " << a << " and " << b << endl;

        powerArgs(&a, &b);// Raise the first number to the power of the second number
        cout << "After raising to the power, the numbers are: " << a << " and " << b << endl;

        break;
    }// b must be greater than 0
    
    cout << "\nEnd of program. Goodbye!" << endl; // End message

    return 0;
}

// Function definitions
void swapArgs(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}// Swap the values of a and b

void divideArgs(int *a, int *b) {
    //variable declarations
    int remainder;
    int quotient;

    quotient = *a / *b;// Calculate the quotient
    remainder = *a % *b;// Calculate the remainder
    *a = quotient;
    *b = remainder;
}// division function

void powerArgs(int *a, int *b) {
    int base = *a;
    int exponent = *b;
    int result = 1;

    for (int i = 0; i < exponent; ++i) {
        result *= base;
    }
    *a = result;
}// power function