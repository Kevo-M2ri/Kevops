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

void Menu();
int ReadValidatChoice(string prompt);
double MonthlyCharge(double charge);

int main() {
    int option;
    double costOfMembership;
    cout << "Hello!!\n";
    cout << "Welcome to the Health Club information.\n";
    cout << "Select a class from here below. (4 to quit)" << endl;
    do {
        Menu();
        double CalcCharges(costOfMembership);
    }
    while(option != QUIT_CHOICE);

    return 0;
}

void Menu() {
    cout << "\nHEALTH CLUB MEMBERSHIP.\n";
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
    }
    while (!dataValidity);

    return choice;
}

double  CalcCharges(double totalCharges) {
    int months;
    int userChoice;
    bool monthsValidity = false;
    userChoice = ReadValidateChoice("Enter your choice (1-4:): ");
    if (userChoice != QUIT_CHOICE) {
        do {
            cout << "For how many months? (1-60)";
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

            switch (userChoice) {
                case ADULT_CHOICE:
                    totalCharges = months * ADULT_FEE;
                    break;
                case CHILD_CHOICE:
                    totalCharges = months * CHILD_FEE;
                    break;
                case SENIOR_CHOICE:
                    totalCharges =months * SENIOR_FEE;
                    break;
            }
        }
        while (!monthsValidity);
    }

    return totalCharges;
}
