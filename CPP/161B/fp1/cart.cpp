#include "cart.h"// Include the cart header file

// displayMenu function definition
void displayMenu() {
    cout <<"======MENU======" << endl;// menu header
    cout << string(25, '-') << endl; // display a line to separate header from menu items
    cout << "1. Add item to cart" << endl;
    cout << "2. Remove item from cart" << endl;
    cout << "3. Update item in cart" << endl;
    cout << "4. Display cart" << endl;
    cout << "5. Checkout" << endl;
    cout << "\nWhat would you like to do? "; // Prompt user for choice
} // end of displayMenu function

int getMenuChoice() {
    int choice; // declare variable to store user's choice

    cin >> choice; // get user's choice
    while (cin.fail() || choice < 1 || choice > 5) {
        cin.clear(); // clear error flag
        cin.ignore(1000, '\n'); // clear input buffer
        cout << "Invalid choice. Please enter a number between 1 and 5: "; // prompt user to enter a valid choice
        cin >> choice; // get user's choice
    } // validate user's choice
    cin.ignore(1000, '\n'); // clear input buffer

    return choice; // return user's choice
} // end of getMenuChoice function

// addItem function definition
void addItem(Cart cart[], int& itemCount) {
    if (itemCount >= MAX_SIZE) {
        cout << "Cart is full. Cannot add more items." << endl; // display message if cart is full
        return; // exit function
    } // check if cart is full

    Cart newItem; // declare variable to store new item details

    cout << "\nEnter item name: "; // prompt user to enter item name
    cin.getline(newItem.name, 50); // get item name

    cout << "Enter item price: "; // prompt user to enter item price
    cin >> newItem.price; // get item price

    while (cin.fail() || newItem.price < 1) {
        cin.clear(); // clear error flag
        cin.ignore(1000, '\n'); // clear input buffer
        cout << "Invalid price. Please enter a positive number: "; // error message
        cin >> newItem.price; // get item price
    } // validate item price

    cout << "Enter item quantity: "; // prompt user to enter item quantity
    cin >> newItem.quantity; // get item quantity

    while(cin.fail() || newItem.quantity < 1) {
        cin.clear(); // clear error flag
        cin.ignore(1000, '\n'); // clear input buffer
        cout << "Invalid quantity. Please enter a positive number: "; // error message
        cin >> newItem.quantity; // get item quantity
    }// validate item quantity

    cart[itemCount] = newItem; // add new item to cart
    itemCount++; // increment item count
    
    cin.ignore(1000, '\n'); // clear input buffer
}

void removeItem(Cart cart[], int& itemCount) {
    if (itemCount == 0) {
        cout << "Cart is empty. Cannot remove items." << endl; // display message if cart is empty
        return; // exit function
    }

    showItemsList(cart, itemCount); // display items in the cart

    int itemNumber; // declare variable to store item number
    cout << "Enter the item number to remove: "; // prompt user to enter item number
    cin >> itemNumber;// get item number

    while(!validateItemNumber(itemNumber, itemCount)) {
        cout << "Invalid item number. Please enter a number between 1 and " << itemCount << ": "; // error message
        cin.clear();// clear error flag
        cin.ignore(1000, '\n');// clear input buffer
        cin >> itemNumber;// get item number
    }// validate item number

    for (int i = itemNumber - 1; i < itemCount - 1; i++) {
        cart[i] = cart[i + 1];
    } // remove item from cart

    itemCount--; // decrement item count
    cin.ignore(1000, '\n');// clear input buffer
}

void updateItem(Cart cart[], int itemCount) {
    if (itemCount == 0) {
        cout << "Cart is empty. Cannot update items." << endl; // display message if cart is empty
        return; // exit function
    } // check if cart is empty

    showItemsList(cart, itemCount); // display items in the cart

    int itemNumber; // declare variable to store item number
    cout << "Enter the item number to update: ";// prompt user to enter item number
    cin >> itemNumber;// get item number

    while(!validateItemNumber(itemNumber, itemCount)) {
        cout << "Invalid item number. Please enter a number between 1 and " << itemCount << ": "; // error message
        cin.clear(); // clear error flag
        cin.ignore(1000, '\n'); // clear input buffer
        cin >> itemNumber; // get item number
    }// validate item number

    cin.ignore(1000, '\n');// clear input buffer

    cout << "Enter new item name: "; // prompt user to enter new item name
    cin.getline(cart[itemNumber - 1].name, 50); // get new item name

    cout << "Enter new item price: $"; // prompt user to enter new item price
    cin >> cart[itemNumber - 1].price; // get new item price

    while (cin.fail() || cart[itemNumber - 1].price < 0) {
        cin.clear(); // clear error flag
        cin.ignore(1000, '\n'); // clear input buffer
        cout << "Invalid price. Please enter a positive number: $"; // error message
        cin >> cart[itemNumber - 1].price; // get new item price
    }// validate new item price

    cout << "Enter new item quantity: "; // prompt user to enter new item quantity
    cin >> cart[itemNumber - 1].quantity; // get new item quantity

    while (cin.fail() || cart[itemNumber - 1].quantity < 1) {
        cin.clear(); // clear error flag
        cin.ignore(1000, '\n'); // clear input buffer
        cout << "Invalid quantity. Please enter a positive number: "; // error message
        cin >> cart[itemNumber - 1].quantity; // get new item quantity
    } // validate new item quantity

    cin.ignore(1000, '\n'); // clear input buffer
} // end of updateItem function

// displayCart function definition
void checkout(const Cart cart[], int itemCount) {
    if (itemCount == 0) {
        cout << "Cart is empty. Cannot checkout." << endl;
        return; // exit function
    }// check if cart is empty

    cout << "Items in cart:" << endl; // display message
    showItemsList(cart, itemCount); // display items in the cart

    double total = calculateCartTotal(cart, itemCount); // calculate total cost of items in the cart
    cout << "Total: $" << fixed << setprecision(2) << total << endl; // display total cost
    cout << "\nThank you for shopping with us!" << endl;// display message
}// end of displayCart function

// calculateItemTotal function definition
double calculateItemTotal(const Cart& item) {
    return item.price * item.quantity; // calculate and return total cost of an item
}// end of calculateItemTotal function

// calculateCartTotal function definition
double calculateCartTotal(const Cart cart[], int itemCount) {
    double total = 0.0; // declare variable to store total cost
    for (int i = 0; i < itemCount; i++) {
        total += calculateItemTotal(cart[i]); // calculate total cost of items in the cart
    } // loop through items in the cart
    return total;// return total cost
}// end of calculateCartTotal function

// showItemsList function definition
void showItemsList(const Cart cart[], int itemCount) {
    if (itemCount == 0) {
        cout << "Cart is empty." << endl;// display message if cart is empty
        return;// exit function
    }// check if cart is empty

    else {
        cout << left << setw(6) << "No." << setw(19) << "Name" << setw(10) << "Price"; // display header
        cout << setw(12) << "Quantity" << setw(20) << "Total Cost" << endl;// display header
        cout << string(58, '-') << endl; // display a line to separate header from items

        for (int i = 0; i < itemCount; i++) {
            cout << left << setw(6) << i + 1; // display item number
            cout << setw(19) << cart[i].name; // display item name
            cout << "$" << fixed << setprecision(2) << setw(13) << cart[i].price;// display item price
            cout << setw(10) << cart[i].quantity; // display item quantity
            cout << "$" << fixed << setprecision(2) << setw(15) << calculateItemTotal(cart[i]) << endl; // display total cost of item
        } // loop through items in the cart
    }// check if cart is not empty

    cout << endl;
}// end of showItemsList function

// validateItemNumber function definition
bool validateItemNumber(int& itemNumber, int itemCount) {
    return !cin.fail() && itemNumber >= 1 && itemNumber <= itemCount; // validate item number
} // end of validateItemNumber function