/******************************************************************************
# Author:           Kelvin Muturi
# Lab:              Discussion #7
# Date:             March 15, 2025
# Description:      This program  
# Input:            
# Output:           
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
        cout << "Enter your choice (1-6): "; // Prompt user for choice
        cin >> choice; // Read user input
        
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
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
        
        if (choice != 6) {
            cout << "\nPress Enter to continue...";
            clearInputBuffer();//input buffer clear function call
            cin.get();
        }// check if choice is not 6 and clear input buffer
        
    } while (choice != 6);// loop until user chooses to quit
    
    return 0;
}