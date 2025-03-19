/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        March 19, 2025
   Assignment:  CS-161B Assignment a07
   Description: This program simulates a shopping cart where the user can add,
                remove, update, and display items in the cart. The user can also
                checkout and see the total cost of the items in the cart. it uses
                a struct to store the item details and functions to perform the
                operations on the cart.
   Inputs:      Item name as a character array, price as a double, quantity and
                item number as integers.
   Outputs:     Item details, cart details as character arrays, price of items,
                and total cost of items in the cart as doubles.
   -------------------------------------------------------------------------**/

#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;
struct Cart {
    char name[50];
    double price;
    int quantity;
};

void displayMenu();
void addItem(Cart cart[], int& itemCount);
void removeItem(Cart cart[], int& itemCount);
void updateItem(Cart cart[], int itemCount);
void displayCart(const Cart cart[], int itemCount);
void checkout(const Cart cart[], int itemCount);
int getMenuChoice();
double calculateItemTotal(const Cart& item);
double calculateCartTotal(const Cart cart[], int itemCount);
void showItemsList(const Cart cart[], int itemCount);
bool validateItemNumber(int& itemNumber, int itemCount);

const int MAX_SIZE = 20;// Maximum number of items in the cart

int main() {
    Cart cart[MAX_SIZE];
    int itemCount = 0;
    int choice;

    cout << "Welcome to the shopping cart!" << endl << endl;

    do {
        displayMenu();
        choice = getMenuChoice();

        switch (choice) {
            case 1:
                addItem(cart, itemCount);
                break;
            case 2:
                removeItem(cart, itemCount);
                break;
            case 3:
                updateItem(cart, itemCount);
                break;
            case 4:
                showItemsList(cart, itemCount);
                break;
            case 5:
                checkout(cart, itemCount);
                break;
            default:
                cout << "Goodbye!" << endl;
        }
    } while (choice != 5);

    return 0;
}

void displayMenu() {
    cout <<"======MENU======" << endl;
    cout << string(25, '-') << endl;
    cout << "1. Add item to cart" << endl;
    cout << "2. Remove item from cart" << endl;
    cout << "3. Update item in cart" << endl;
    cout << "4. Display cart" << endl;
    cout << "5. Checkout" << endl;
    cout << "\nWhat would you like to do? ";
}

int getMenuChoice() {
    int choice;
    cin >> choice;
    while (cin.fail() || choice < 1 || choice > 5) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid choice. Please enter a number between 1 and 5: ";
        cin >> choice;
    }
    cin.ignore(1000, '\n');

    return choice;
}

void addItem(Cart cart[], int& itemCount) {
    if (itemCount >= MAX_SIZE) {
        cout << "Cart is full. Cannot add more items." << endl;
        return;
    }

    Cart newItem;

    cout << "\nEnter item name: ";
    cin.getline(newItem.name, 50);

    cout << "Enter item price: ";
    cin >> newItem.price;

    while (cin.fail() || newItem.price < 1) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid price. Please enter a positive number: ";
        cin >> newItem.price;
    }

    cout << "Enter item quantity: ";
    cin >> newItem.quantity;

    while( cin.fail() || newItem.quantity < 1) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid quantity. Please enter a positive number: ";
        cin >> newItem.quantity;
    }

    cart[itemCount] = newItem;
    itemCount++;
    
    cin.ignore(1000, '\n');
}

void removeItem(Cart cart[], int& itemCount) {
    if (itemCount == 0) {
        cout << "Cart is empty. Cannot remove items." << endl;
        return;
    }

    showItemsList(cart, itemCount);

    int itemNumber;
    cout << "Enter the item number to remove: ";
    cin >> itemNumber;

    while(!validateItemNumber(itemNumber, itemCount)) {
        cout << "Invalid item number. Please enter a number between 1 and " << itemCount << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> itemNumber;
    }

    for (int i = itemNumber - 1; i < itemCount - 1; i++) {
        cart[i] = cart[i + 1];
    }

    itemCount--;
    cin.ignore(1000, '\n');
}

void updateItem(Cart cart[], int itemCount) {
    if (itemCount == 0) {
        cout << "Cart is empty. Cannot update items." << endl;
        return;
    }

    showItemsList(cart, itemCount);

    int itemNumber;
    cout << "Enter the item number to update: ";
    cin >> itemNumber;

    while(!validateItemNumber(itemNumber, itemCount)) {
        cout << "Invalid item number. Please enter a number between 1 and " << itemCount << ": ";
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> itemNumber;
    }

    cin.ignore(1000, '\n');

    cout << "Enter new item name: ";
    cin.getline(cart[itemNumber - 1].name, 50);

    cout << "Enter new item price: $";
    cin >> cart[itemNumber - 1].price;

    while (cin.fail() || cart[itemNumber - 1].price < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid price. Please enter a positive number: $";
        cin >> cart[itemNumber - 1].price;
    }

    cout << "Enter new item quantity: ";
    cin >> cart[itemNumber - 1].quantity;

    while( cin.fail() || cart[itemNumber - 1].quantity < 1) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid quantity. Please enter a positive number: ";
        cin >> cart[itemNumber - 1].quantity;
    }

    cin.ignore(1000, '\n');
}

void checkout(const Cart cart[], int itemCount) {
    if (itemCount == 0) {
        cout << "Cart is empty. Cannot checkout." << endl;
        return;
    }

    cout << "Items in cart:" << endl;
    showItemsList(cart, itemCount);

    double total = calculateCartTotal(cart, itemCount);
    cout << "Total: $" << fixed << setprecision(2) << total << endl;
    cout << "\nThank you for shopping with us!" << endl;
}

double calculateItemTotal(const Cart& item) {
    return item.price * item.quantity;
}

double calculateCartTotal(const Cart cart[], int itemCount) {
    double total = 0.0;
    for (int i = 0; i < itemCount; i++) {
        total += calculateItemTotal(cart[i]);
    }
    return total;
}

void showItemsList(const Cart cart[], int itemCount) {
    if (itemCount == 0) {
        cout << "Cart is empty." << endl;
        return;
    }

    else {
        cout << left << setw(6) << "No." << setw(19) << "Name" << setw(10) << "Price" << setw(12) << "Quantity" << setw(20) << "Total Cost" << endl;
        cout << string(58, '-') << endl;

        for (int i = 0; i < itemCount; i++) {
            double itemTotal = calculateItemTotal(cart[i]);
            cout << left << setw(6) << i + 1;
            cout << setw(19) << cart[i].name;
            cout << "$" << fixed << setprecision(2) << setw(13) << cart[i].price;
            cout << setw(10) << cart[i].quantity;
            cout << "$" << fixed << setprecision(2) << setw(15) << calculateItemTotal(cart[i]) << endl;
        }
    }

    cout << endl;
}

bool validateItemNumber(int& itemNumber, int itemCount) {
    return !cin.fail() && itemNumber >= 1 && itemNumber <= itemCount;
}