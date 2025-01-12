/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        January 12, 2025
   Assignment:  CS-161B Assignment a01
   Description: This program gives the user a menu with choices, allowing them
                to pick a choice, then asks them some questions, giving them
                results whilst checking the validity of their responses. It
                then calculates the amount they will pay including tips and the
                disount they are to receive if the meet the discount criteria.
   Inputs:      option as an integer, cost and tip as doubles, anotherOrder as
                a character
   Outputs:     alltotal and discount as doubles
   -----------------------------------------------------------------------**/

#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <cctype>
using namespace std;


// function prototypes
void welcome();
void displayMenu();
void readOption(int &option);
void readInt(string prompt, int &num);
void readDouble(string prompt, double &num);
void placeOrder(double &cost);
double tipDiscount(double &tip, double &discount, double cost);
void goodbye();

// main program
int main() {
    // variables declarations
    int option = 0;
    double cost = 0.0;
    double tip = 0.0;
    double discount = 0.0;
    double allTotal = 0.0;

    // welcome function call
    welcome();
    
    // menu display loop
    do {
        // menu function call
        displayMenu();
        // choice_on_menu function call
        readOption(option);

        // choosing to proceed condition
        if (option == 1) {

            //user input function call
            placeOrder(cost);

            cout << fixed << setprecision(2);
            cout << "Your total is: $" << cost << endl; // total cost of items output

            // cost to be incurred after discount and tip
            allTotal = tipDiscount(tip, discount, cost);

            cout << "\nYour total is: $" << cost + tip << endl; // cost to be incurred before discount output
            if (discount > 0) {
                cout << "You get a discount of: $" << discount << endl; //discount amount output
            }
            cout << "Your calculated total cost is: $" << allTotal << endl; //cost to be incurred after discount and tip output
        }
    } while (option != 2); //condition for termination

    return 0;
}
// end main

//welcome function
void welcome() {
    cout << "Hello!! Welcome to the Food Cart." << endl;
    
}

//menu display function
void displayMenu() {
    cout << "What would you like for today?" << endl;
    cout << "Choose from the options below:" << endl;
    cout << setw(5) << left << "1.";
    cout << "Place an order" << endl;
    cout << setw(5) << left << "2.";
    cout << "Quit" << endl;
}

// integer entry and validation function
void readInt(string prompt, int &num) {
    bool validInts = false;

    while (!validInts) {
        cout << prompt;
        cin >> num;

        if (cin.fail() || num <= 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid option! Please enter a positive number." << endl; // error message
        } //loop condition
        else {
            validInts = true;
        }
    } // data validation loop
}

// user entry choice function
void readOption(int &option) {
    do {
        readInt("Please choose 1 (Place an order) or 2 (Quit): ", option);
        if (option != 1 && option != 2) {
            cout << "Invalid Option! Please choose 1 or 2!" << endl;
        }
    } while (option != 1 && option != 2);
}

// floating point entry and validation function
void readDouble(string prompt, double &num) {
    bool validDouble = false;
    while (!validDouble) {
        cout << prompt;
        cin >> num;

        if (cin.fail() || num < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error on Input. Invalid number entered. Please enter a non negative number." << endl;
        } //loop condition
        else {
            validDouble = true;
        }
    }
}
 // repeat to choose or finish function
void placeOrder(double &cost) {
    cost = 0.0;
    string orderName;
    double itemCost = 0.0;
    char anotherOrder = 'y';

    while (anotherOrder == 'y' || anotherOrder == 'Y') {
        cout << "Enter the name of the item you'd like: " << endl;
        cin.ignore();
        getline(cin, orderName);

        readDouble("Enter the cost of your choice item $: ", itemCost);
        cost += itemCost;

        anotherOrder = ' ';
        while (anotherOrder != 'y' && anotherOrder != 'n' && anotherOrder != 'Y' && anotherOrder != 'N') {
            cout << "Do you want another item? (y/n): ";
            cin >> anotherOrder;

            if (anotherOrder != 'y' && anotherOrder != 'n' && anotherOrder != 'Y' && anotherOrder != 'N') {
                cout << "invalid option. Please choose y/n!" << endl;
            } 
        } // loop condition
    } //entry loop
}

// discount, tip and total cost function
double tipDiscount(double &tip, double &discount, double cost) {
    double totalWithTip = 0.0;
    readDouble("Enter the amount of tip you want to add $: ", tip);
    totalWithTip = cost + tip;

    //discount conditions
    if (totalWithTip >= 50.0) {
        discount = totalWithTip * 0.10;
    }
    else if (totalWithTip >= 35.0) 
    {
        discount = totalWithTip * 0.05;
    }
    else {
        discount = 0.0;
    }

    return totalWithTip -= discount;
}


//goodbye function
void goodbye() {
    cout << "Thank you for using our program. Goodbye!" << endl;
}