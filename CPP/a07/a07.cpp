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

using namespace std;

// constant declaration
const double BEVERAGE_COST = 0.25;

// function main
int main () {
    // variables declaration
    int coinVal = 0;
    int allCoinsVal = 0;
    double amountInDollars = 0.0;
    char choice;
    int numCups;

    // welcome message
    cout << "Hello! Welcome to our coffee and tea dispenser!!\n" << endl;

    // input loop
    do {
        cout << "Please input your coins - 5, 10, or 25 (0 to exit): ";
        cin >> coinVal;
        // inacceptable coins continuous skip condition
        while ((coinVal != 5) || (coinVal != 10) || (coinVal != 25))
        {
            continue;
        }
        allCoinsVal += coinVal; // test me
    }
    while (coinVal != 0); // condition to loop again

    amountInDollars = static_cast<double>(allCoinsVal) / 100; // amount in dollars
    cout << fixed << setprecision(2) << endl; // two decimal places condition
    cout << "\nThe amount you entered is: $" << amountInDollars << endl;

    // menu
    cout << "\nChoose your beverage ($" << BEVERAGE_COST << " each: )" << endl;
    cout << setw(5) << right << "C/c: Coffee" << endl;
    cout << setw(5) << right << "T/t: Tea" << endl;
    cout << setw(5) << right << "Q/q: Quit" << endl;

    // customer choices
    while ((choice != 'q') || (choice != 'Q')) {
        cin >> choice;
        if ((choice == 'C') || (choice == 'c') || (choice = 't') || (choice == 'T')) {
            cout <<  "How many cups would like? " << endl;
            cin >> numCups;
            if (cin.fail()) {
                cin.clear();
                cin.ignore();
                cout << "Invalid option!!" << endl;
                continue;
           }
        }
        else {
            cout << "Invalid choice! Please try again!" << endl;
            continue;
        }
    }
    

    return 0;
}