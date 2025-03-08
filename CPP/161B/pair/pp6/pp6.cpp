#include "pointer.h"
#include <iostream>
#include <limits>

using namespace std;

int main() {
    int choice = 0;
    
    cout << "=== C++ Asterisk (*) Operator Tutorial ===" << endl;
    cout << "This program will help you understand the different ways" << endl;
    cout << "the asterisk (*) operator is used in C++." << endl << endl;
    
    do {
        displayMenu();
        cout << "Enter your choice (1-6): ";
        cin >> choice;
        
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number between 1 and 6." << endl;
            clearInputBuffer();
            continue;
        }
        
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
                
            case 5: // Resources
                displayResources();
                break;
                
            case 6: // Quit
                cout << "Thank you for learning about the asterisk operator in C++!" << endl;
                cout << "Goodbye!" << endl;
                break;
                
            default:
                cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
        }
        
        if (choice != 6) {
            cout << "\nPress Enter to continue...";
            clearInputBuffer();
            cin.get();
        }
        
    } while (choice != 6);
    
    return 0;
}