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
    double balance = 0.0;

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
    cout << "\nHere is our menu. Choose your beverage ($" << BEVERAGE_COST << " each.): " << endl;
    cout << "C/c: Coffee" << endl;
    cout << "T/t: Tea" << endl;
    cout << "Q/q: Quit" << endl;

    // customer choices
    while (!quitProgram) {
        do {
            cout << "Ready to make an order? Input here: " << endl;
            cin >> choice;
            validChoice = (tolower(choice) == 'c' || tolower(choice) == 't' || tolower(choice) == 'q');
                if (!validChoice) {
                    cout << "Invalid Option! Please choose a valid option!\n";
            }
        } while (!validChoice);

        if (tolower(choice) == 'q') {
            cout << "\nYour balance: $" << amountInDollars << endl;
            cout << "\nThank you for using my Vending Machine Program!\n";
            quitProgram = true;
            continue; // Avoid further processing after quit
        }

        do {
            cout << "How many would you like?\n>> ";
            cin >> numCups;

            while (cin.fail() || numCups <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Option! Please enter a positive number.\n>> ";
                cin >> numCups;
            }
        } while (numCups <= 0);

        totalCost = BEVERAGE_COST * numCups;

        if (amountInDollars >= totalCost) {
            balance = amountInDollars - totalCost;
            cout << "\nYour total: $" << totalCost << "\nYour balance: $" << balance << "\n" << endl;
            cout << "Thank you for using my Vending Machine Program!\n";
            quitProgram = true;
        }
        else {
            cout << "\nInsufficient balance! Your total is $" << totalCost
                 << ", but you have entered is $" << amountInDollars << ".\n";
            cout << "Please add more coins.\n" << endl;

            do {
                cout << "Please input additional coins - 5, 10, or 25 (0 to exit): ";
                cin >> coinVal;
                // inacceptable coins continuous skip condition
                while (cin.fail() || (coinVal != 0 && coinVal != 5 && coinVal != 10 && coinVal != 25)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid coin! Please enter 5, 10, or 25 only (Enter 0 to finish): ";
                    cin >> coinVal;
                }

            allCoinsVal += coinVal; // test me
            }
            while (coinVal != 0); // condition to loop again
        }
    }
        
    return 0;
}