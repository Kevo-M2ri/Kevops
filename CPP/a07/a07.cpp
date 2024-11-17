/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        November 17, 2024
   Assignment:  CS-161A Assignment a06
   Description: This program asks the user to input the number of 
   Inputs:      
   Outputs:     
   -----------------------------------------------------------------------****/

#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;

// constant declaration
const double BEVERAGE_COST = 0.25;

// function main
int main () {
    // variables declaration

    int coinVal = 0; // input for coins
    int allCoinsVal = 0; // sum of coins
    double amountInDollars = 0.0; // total amount in dollars
    char choice = '\0'; // menu options
    int numCups = 0;
    double totalCost = 0.0; // items number
    bool validChoice;
    bool quitProgram = false;

    // welcome message
    cout << "Hello! Welcome to our coffee and tea dispenser!!\n" << endl;

    // input loop
    do {
        cout << "Please input your coins - 5, 10, or 25 (0 to exit): ";
        cin >> coinVal;
        // inacceptable coins continuous skip condition
        while (cin.fail() || (coinVal != 0 && coinVal != 5 && coinVal != 10 && coinVal != 25)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid coin! Please enter 5, 10, or 25 only (Enter 0 to finish): ";
            cin >> coinVal;
        }

        allCoinsVal += coinVal; // test me
    } while (coinVal != 0); // condition to loop again

    amountInDollars = static_cast<double>(allCoinsVal) / 100; // amount in dollars
    cout << fixed << setprecision(2) << endl; // two decimal places condition
    cout << "\nThe amount you entered is: $" << amountInDollars << endl;

    // menu
    cout << "\nChoose your beverage ($" << BEVERAGE_COST << " each.): " << endl;
    cout << setw(5) << right << "C/c: Coffee" << endl;
    cout << setw(5) << right << "T/t: Tea" << endl;
    cout << setw(5) << right << "Q/q: Quit" << endl;

    // customer choices
    while (!quitProgram) {
        do {
            cin >> choice;
            validChoice = (tolower(choice) == 'c' || tolower(choice) == 't' || tolower(choice) == 'q');
                if (!validChoice) {
                    cout << "Invalid Option! Please choose a valid option!\n";
            }
        } while (!validChoice);
    }
        
    return 0;
}