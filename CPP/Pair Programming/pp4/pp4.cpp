/******************************************************************************
# Author:           Kelvin Muturi
# Lab:              Discussion #8
# Date:             November 24, 2024
# Description:      This program displays a menu and asks the user to make a
#                   selection. A do-while loop repeats the program until the
#                   user selects item 4 from the menu.
# Input:            integer membership category, integer months
# Output:           float membership costs
# Sources:          None
#******************************************************************************/
#include <iostream>
#include <iomanip>
#include <limits>
#include <string>

using namespace std;

// Constants for menu choices
const int ADULT_CHOICE = 1;
const int CHILD_CHOICE = 2;
const int SENIOR_CHOICE = 3;
const int QUIT_CHOICE = 4;

// Constants for membership rates
const double ADULT_FEE = 40.0;
const double CHILD_FEE = 20.0;
const double SENIOR_FEE = 30.0;


// function prototypes
void Menu();
int ReadValidateChoice(string prompt);
int ReadValidateMonths(string prompt);
double CalcCharges(int userChoice, int months);

int main() {
    int option;
    int numMonths;
    double costOfMembership;
    double totalCostForMembers = 0.0;

    // welcome message
    cout << "Hello!!\n";
    cout << "Welcome to the Health Club information.\n";
    cout << "Select a class from here below. (4 to quit)" << endl;

    cout << fixed << setprecision(2); // set output doubles to 2 dp

    do {
        Menu();
        option = ReadValidateChoice("\nEnter your choice (1-4): ");

        if (option != QUIT_CHOICE) { // If user didn't choose to quit
            numMonths = ReadValidateMonths("For how many months (1-60)? ");
            costOfMembership = CalcCharges(option, numMonths); // Calculate charges
            cout << "The mbership cost is: $" << costOfMembership << endl;

            totalCostForMembers += costOfMembership;
        }
    }
    while(option != QUIT_CHOICE); // repeat until user chooses to quit
    cout << "\nThe total cost of all members for the months entered is: $" << totalCostForMembers << endl;

    cout << "\nThank you for using the Health Club Membership Program! >>>> Goodbye!" << endl;

    return 0;
}

//menu function
void Menu() {
    cout << "\nHEALTH CLUB MEMBERSHIP.\n";
    cout << "----------------------------\n";
    cout << "1. Standard Adult Membership.\n";
    cout << "2. Child Membership\n";
    cout << "3. Senior Citizen Membership\n";
    cout << "4. Quit the Program" << endl;
}

int ReadValidateChoice(string prompt) {
    int choice;
    bool dataValidity = false;
    do {
        cout << prompt;
        cin >> choice;
        if (cin.fail() || choice < ADULT_CHOICE || choice > QUIT_CHOICE) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!! Please enter between 1-4";
        }
        else {
            dataValidity = true;
        }
    } while (!dataValidity);

    return choice;
}

int ReadValidateMonths(string prompt) {
    int months;
    bool monthsValidity = false;

    do {
        cout << prompt;
        cin >> months;

        if (cin.fail() || months <= 0 || months > 60) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!! Membership can only be between 1 to 60 months inclusive\n";
            cout << "Please enter between 1 and 60: ";
        }
        else {
            monthsValidity = true;
        }
    } while (!monthsValidity);

    return months;
}

double  CalcCharges(int userChoice, int months) {
    double totalCharges = 0.0;

    switch (userChoice) {
        case ADULT_CHOICE:
            totalCharges = months * ADULT_FEE;
            break;
        case CHILD_CHOICE:
            totalCharges = months * CHILD_FEE;
            break;
        case SENIOR_CHOICE:
            totalCharges = months * SENIOR_FEE;
            break;
    }

    return totalCharges;
}
