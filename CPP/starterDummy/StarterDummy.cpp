#include <iostream>
#include <iomanip>
#include <cctype>
#include <limits>

using namespace std;

// Constants for item costs
const double ITEM_COST = 0.25;

int main() {
    double balance = 0.0; // Accumulator for user balance
    int coin = 0;        // User input for coins
    char option = '\0';  // User menu choice
    int quantity = 0;    // Quantity of items
    double totalCost = 0.0; // Accumulator for total cost
    bool validChoice;    // Flag for menu choice validation

    // Welcome message
    cout << "Welcome to my Coffee/Tea Vending Machine!\n" << endl;

    // Coin collecting loop
    do {
        cout << "Enter coins - 5, 10, or 25 only (Enter 0 to finish): ";
        cin >> coin;

        while (cin.fail() || (coin != 0 && coin != 5 && coin != 10 && coin != 25)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid coin! Please enter 5, 10, or 25 only (Enter 0 to finish): ";
            cin >> coin;
        }

        balance += coin / 100.0; // Add valid coins to balance
    } while (coin != 0);

    // Output the balance
    cout << fixed << setprecision(2);
    cout << "\nYour balance is $" << balance << "\n" << endl;

    // Main menu loop
    bool exitProgram = false;
    while (!exitProgram) {
        // Display the menu and validate the choice
        do {
            cout << "Please pick an option ($0.25 each):\n"
                 << "    C/c: Coffee\n"
                 << "    T/t: Tea\n"
                 << "    Q/q: Quit\n>> ";
            cin >> option;

            validChoice = (tolower(option) == 'c' || tolower(option) == 't' || tolower(option) == 'q');
            if (!validChoice) {
                cout << "Invalid Option! Please choose a valid option!\n";
            }
        } while (!validChoice);

        // Process Quit option
        if (tolower(option) == 'q') {
            cout << "\nYour balance: $" << balance << endl;
            cout << "\nThank you for using my Vending Machine Program!\n";
            exitProgram = true;
            continue; // Avoid further processing after quit
        }

        // Process Coffee or Tea selection
        do {
            cout << "How many would you like?\n>> ";
            cin >> quantity;

            while (cin.fail() || quantity <= 0) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Option! Please enter a positive number.\n>> ";
                cin >> quantity;
            }
        } while (quantity <= 0);

        // Calculate total cost for current order
        totalCost = ITEM_COST * quantity;

        // Check if balance is sufficient
        if (balance >= totalCost) {
            balance -= totalCost;
            cout << "\nYour total: $" << totalCost << "\nYour balance: $" << balance << "\n" << endl;
            cout << "Thank you for using my Vending Machine Program!\n";
            exitProgram = true;
        } else {
            cout << "\nInsufficient balance! Your total is $" << totalCost
                 << ", but your balance is $" << balance << ".\n";
            cout << "Please add more coins.\n" << endl;

            // Collect additional coins
            do {
                cout << "Enter coins - 5, 10, or 25 only (Enter 0 to finish): ";
                cin >> coin;

                while (cin.fail() || (coin != 0 && coin != 5 && coin != 10 && coin != 25)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid coin! Please enter 5, 10, or 25 only (Enter 0 to finish): ";
                    cin >> coin;
                }

                balance += coin / 100.0;
            } while (coin != 0);
        }
    }

    return 0;
}