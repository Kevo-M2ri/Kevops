/******************************************************************************
# Author:           Kelvin Muturi
# Lab:              Discussion #7
# Date:             March 15, 2025
# Description:      This program shows the different uses of the asterisk (*)
                    operator in C++. It includes multiplication, pointer
                    declaration, pointer dereference, and struct pointers. It
                    uses functions to demonstrate each use case and provides a
                    menu for user interaction. The program also includes input
                    validation.
# Input:            User inputs a number between 1 and 6 to select the demonstration
                    they want to see. For multiplication, the user inputs two
                    numbers. For pointer declaration, the user inputs an integer
                    value and a name. For pointer dereference, the user inputs an
                    integer value. For struct pointers, the user inputs a name,
                    age, and height.
# Output:           various outputs depending on the user's choice. It includes the result
                    of multiplication, the memory address of variables, and the
                    contents of a struct. The program also handles invalid input
                    gracefully and provides a menu for user interaction.
# Sources:          
#******************************************************************************/

#include "pointer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    int choice = 0; // Initialize choice to 0
    
    //banner
    cout << "==========================================================" << endl;
    cout << "Welcome to the Asterisk Operator Demonstration!" << endl;
    cout << "This program will help you understand the different ways" << endl;
    cout << "the asterisk (*) operator is used in C++." << endl;
    cout << "==========================================================" << endl << endl;
    
    do {
        displayMenu();// Display the menu function call
        cout << "Enter your choice (1-5): "; // Prompt user for choice
        cin >> choice; // Read user input
        
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            clearInputBuffer();
            continue;
        } //check input validity and clear input buffer
        
        switch (choice) {
            case 1: // Multiplication
                demonstrateMultiplication();
                break;
                
            case 2: // Pointer Declaration
                demonstratePointerDeclaration();
                break;
                
            case 3: // Pointer Dereference
                demonstratePointerDereference();
                break;
                
            case 4: // Struct Pointers
                demonstrateStructPointers();
                break;
                
            case 5: // Quit
                cout << "Thank you for learning about the asterisk operator in C++!" << endl;
                cout << "Goodbye!" << endl;
                break;
                
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
        
        if (choice != 5) {
            cout << "\nPress Enter to continue...";
            clearInputBuffer();//input buffer clear function call
            cin.get();
        }// check if choice is not 6 and clear input buffer
        
    } while (choice != 5);// loop until user chooses to quit
    
    return 0;
}