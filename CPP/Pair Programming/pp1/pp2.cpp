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
    int totalChange;
    int numDollars;
    int numQuarters;
    int numDimes;
    int numNickels;
    int numPennies;

    cout << "Enter your change amount: ";
    cin >> totalChange;

    if (totalChange == 0) {
        cout << "No change." << endl;
    }
    else {
        if (totalChange >= 100) {
            numDollars = totalChange / 100;
            totalChange = totalChange % 100;

            if (numDollars == 1) {
                cout << numDollars << " Dollar" << endl;
            }
            else if (numDollars > 1) {
                cout << numDollars << " Dollars" << endl;
            }
        }
        if ((totalChange >= 25) && (totalChange < 100)) {
            numQuarters = totalChange / 25;
            totalChange = totalChange % 25;

            if (numQuarters == 1) {
                cout << numQuarters << " Quarter" << endl;
            }
            else if (numQuarters > 1) {
                cout << numQuarters << " Quarters" << endl;
            }
        }
        if ((totalChange >= 10) && (totalChange < 25)) {
            numDimes = totalChange / 10;
            totalChange = totalChange % 10;

            if (numDimes == 1) {
                cout << numDimes << " Dime" << endl;
            }
            else if (numDimes > 1) {
                cout << numDimes << " Dimes" << endl;
            }
        }
        if ((totalChange >= 5) && (totalChange < 10)) {
            numNickels = totalChange / 5;
            totalChange = totalChange % 5;

            if (numNickels == 1) {
                cout << numNickels << " Nickel" << endl;
            }
            else if (numNickels > 1) {
                cout << numNickels << " Nickels" << endl;
            }
        }
        if ((totalChange >=1 ) && (totalChange < 5)) {
            numPennies = totalChange;

            if (numPennies == 1) {
                cout << numPennies << " Penny" << endl;
            }
            else if (numPennies > 1) {
                cout << numPennies << " Pennies" << endl;
            }
        }
    }

    return 0;
   }