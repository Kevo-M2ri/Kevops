#include "cart.h"

void displayMenu() {
    cout << "1. Add item to cart" << endl;
    cout << "2. Remove item from cart" << endl;
    cout << "3. Update item in cart" << endl;
    cout << "4. Display cart" << endl;
    cout << "5. Checkout" << endl;
    cout << "What would you like to do? ";
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

    cout << "Enter new item price: ";
    cin >> cart[itemNumber - 1].price;

    while (cin.fail() || cart[itemNumber - 1].price < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid price. Please enter a positive number: ";
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
    cout << "Thank you for shopping with us!" << endl;
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
    cout << left << setw(4) << "Item No." << setw(20) << "Name" << setw(10) << "Price($)" << setw(10) << "Quantity" << setw(10) << "Total Cost($)" << endl;
    cout << string(55, '-') << endl;

    for (int i = 0; i < itemCount; i++) {
        double itemTotal = calculateItemTotal(cart[i]);
        cout << left << setw(4) << i + 1 << ".";
        cout << setw(20) << cart[i].name;
        cout << fixed << setprecision(2) << setw(10) << cart[i].price;
        cout << setw(10) << cart[i].quantity;
        cout << fixed << setprecision(2) << setw(10) << calculateItemTotal(cart[i]) << endl;
    }

    cout << endl;
}

bool validateItemNumber(int& itemNumber, int itemCount) {
    return !cin.fail() && itemNumber >= 1 && itemNumber <= itemCount;
}