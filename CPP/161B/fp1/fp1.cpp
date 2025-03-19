/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        March 19, 2025
   Assignment:  CS-161B Assignment a07
   Description: This program 
   Inputs:      
   Outputs:     
   -------------------------------------------------------------------------**/
#include "cart.h"

int main() {
    Cart cart[MAX_SIZE];
    int itemCount = 0;
    int choice;

    cout << "Welcome to the shopping cart!" << endl;

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