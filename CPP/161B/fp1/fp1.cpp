/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        March 19, 2025
   Assignment:  CS-161B Assignment fp1
   Description: This program simulates a shopping cart where the user can add,
                remove, update, and display items in the cart. The user can also
                checkout and see the total cost of the items in the cart. it uses
                a struct to store the item details and functions to perform the
                operations on the cart.
   Inputs:      Item name, price, quantity, item number to remove/update.
                Menu choice.
   Outputs:     Item details, cart details, total cost of items in the cart.
   -------------------------------------------------------------------------**/
#include "cart.h" // Include the cart header file

// Main function
int main() {
    Cart cart[MAX_SIZE]; // Array of Cart structs
    int itemCount = 0; // Number of items in the cart
    int choice; // User's menu choice

    cout << "Welcome to the shopping cart!" << endl << endl;// Display welcome message

    do {
        displayMenu(); // Display the menu
        choice = getMenuChoice();// Get the user's menu choice

        switch (choice) {
            case 1:
                addItem(cart, itemCount);
                break; // Add an item to the cart
            case 2:
                removeItem(cart, itemCount);
                break; // Remove an item from the cart
            case 3:
                updateItem(cart, itemCount);
                break; // Update an item in the cart
            case 4:
                showItemsList(cart, itemCount);
                break; // Display the items in the cart
            case 5:
                checkout(cart, itemCount);
                break; // Checkout and display the total cost
        }
    } while (choice != 5);// Continue until the user chooses to checkout

    return 0;// Return 0 to indicate successful completion
}// End of main function