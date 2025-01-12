/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        October 20, 2024
   Assignment:  CS-161A Discussion 4
   Description: This program asks the user for the change, calculates and
                outputs the number of dollars, quarters, dimes, nickels and
                pennies separately
   Inputs:      total amount of change
   Outputs:     number of dollars, quarters, dimes, nickels, and pennies
   -----------------------------------------------------------------------****/

#include <iostream>

using namespace std;

int main () {
    // variable declarations
    int totalChange;
    int numDollars;
    int numQuarters;
    int numDimes;
    int numNickels;
    int numPennies;

    // input prompt
    cout << "Enter your change amount: ";
    cin >> totalChange;

    // if change is 0
    if (totalChange == 0) {
        cout << "No change." << endl;
    }

    // change is greater than 0
    else {
        // if change is greater than 99
        if (totalChange >= 100) {
            numDollars = totalChange / 100;
            totalChange = totalChange % 100;

            // output for 1
            if (numDollars == 1) {
                cout << numDollars << " Dollar" << endl;
            }
            // output for more than 1
            else if (numDollars > 1) {
                cout << numDollars << " Dollars" << endl;
            }
        }
        // change in the range 25 to 99
        if ((totalChange >= 25) && (totalChange < 100)) {
            numQuarters = totalChange / 25;
            totalChange = totalChange % 25;

            // output for 1
            if (numQuarters == 1) {
                cout << numQuarters << " Quarter" << endl;
            }
            // output for more than 1
            else if (numQuarters > 1) {
                cout << numQuarters << " Quarters" << endl;
            }
        }
        // change in the range 10 to 24
        if ((totalChange >= 10) && (totalChange < 25)) {
            numDimes = totalChange / 10;
            totalChange = totalChange % 10;

            // output for 1
            if (numDimes == 1) {
                cout << numDimes << " Dime" << endl;
            }
            // output for more than 1
            else if (numDimes > 1) {
                cout << numDimes << " Dimes" << endl;
            }
        }

        // change in the range 5 to 9
        if ((totalChange >= 5) && (totalChange < 10)) {
            numNickels = totalChange / 5;
            totalChange = totalChange % 5;

            // output for 1
            if (numNickels == 1) {
                cout << numNickels << " Nickel" << endl;
            }
            // output for more than 1
            else if (numNickels > 1) {
                cout << numNickels << " Nickels" << endl;
            }
        }

        // change in the range 1 to 4
        if ((totalChange >=1 ) && (totalChange < 5)) {
            numPennies = totalChange;

            // output for 1
            if (numPennies == 1) {
                cout << numPennies << " Penny" << endl;
            }
            // output for more than 1
            else if (numPennies > 1) {
                cout << numPennies << " Pennies" << endl;
            }
        }
    }

    return 0;
   }