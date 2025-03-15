#include "pointer.h"
#include <iostream>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\n=== MENU ===" << endl; //menu banner
    cout << "1. Arithmetic Multiplication Operator" << endl;
    cout << "2. Pointer Declaration Operator" << endl;
    cout << "3. Pointer Dereference (Indirection) Operator" << endl;
    cout << "4. Pointers with User-Defined Structs"<< endl;
    cout << "5. Quit" << endl;
} // Display the menu function

void demonstrateMultiplication() {
    double num1, num2, result; // variables for multiplication
    cout << "\n=== Arithmetic Multiplication Operator ===" << endl; //arithmetic multiplication operator banner
    cout << "In C++, the asterisk (*) is used for multiplication between two numeric values." << endl;
    cout << "Syntax: result = operand1 * operand2;" << endl << endl;
    
    cout << "Enter two numbers to multiply:" << endl;
    cin >> num1 >> num2; // user inputs two numbers
    result = num1 * num2; // Perform multiplication
    
    // Display the result
    cout << "\nExample:" << endl;
    cout << "The result of " << num1 << " * " << num2 << " = " << result << endl; // mathematical operation display
}// demonstrate multiplication function

void demonstratePointerDeclaration() {
    int userValue;
    cout << "\n=== Pointer Declaration Operator ===" << endl;// pointer declaration operator banner
    cout << "The asterisk (*) is used to declare a pointer variable that stores the address of another variable." << endl;
    cout << "Syntax: dataType *pointerName;" << endl << endl;// pointer declaration syntax
    
    cout << "Enter an integer value: ";
    cin >> userValue;// user inputs an integer value
    
    // Create a pointer to the user's value
    int *ptr = &userValue;
    
    cout << "\nHere, we have:" << endl;
    cout << "- userValue: " << userValue << " (the actual value)" << endl;
    cout << "- &userValue: " << &userValue << " (the memory address of userValue)" << endl;
    cout << "- ptr: " << ptr << " (the pointer stores the address of userValue)" << endl;
    cout << "- *ptr: " << *ptr << " (the value at the address stored in ptr)" << endl << endl;
    
    // Demonstrate with char array
    char name[50];// user input for char array
    clearInputBuffer();// clear input buffer
    cout << "Enter your name: ";
    cin.getline(name, 50);// user inputs a name
    
    char *namePtr = name;// Points to the first element

    cout << "\nHere, we have:" << endl;
    cout << "- name: " << name << " (the array contents)" << endl;// contents of the array
    cout << "- name: " << static_cast<void*>(name) << " (the memory address of the array)" << endl;// address of the array
    cout << "- namePtr: " << static_cast<void*>(namePtr) << " (points to the same address)" << endl;// address of the pointer
    cout << "- *namePtr: '" << *namePtr << "' (the first character of the array)" << endl;// first character of the array
    
    cout << "\nNote that the & symbol is the address-of operator, which returns the memory address" << endl;
    cout << "of a variable. It's often used together with the pointer declaration." << endl;
}// demonstrate pointer declaration function

void demonstratePointerDereference() {
    cout << "\n=== Pointer Dereference (Indirection) Operator ===" << endl;// pointer dereference operator banner
    cout << "Once a pointer is declared, the asterisk (*) is used to access the value stored" << endl;
    cout << "at the memory address contained in the pointer. This is called dereferencing." << endl;
    cout << "Syntax: value = *pointerName;" << endl << endl; // dereference syntax
    
    int userValue; //variable for user input
    cout << "Enter an integer value: ";
    cin >> userValue; // user inputs an integer value
    
    // Create a pointer to the user's value
    int *ptr = &userValue;// pointer to the address of userValue
    
    // Modify the value through the pointer
    cout << "Modifying the value using the pointer." << endl;
    cout << "Enter a new value: ";
    cin >> *ptr;// user inputs a new value
    
    cout << "\nAfter modifying: *ptr = " << *ptr << " userValue = " << userValue << endl << endl; // display modified values
    
    // Demonstrate with character array
    char text[50];
    clearInputBuffer();
    cout << "Enter a short sentence: ";
    cin.getline(text, 50);
    
    char *textPtr = text;// pointer to the first character of the array

    // Display each character using pointer arithmetic
    cout << "Accessing each character using pointer dereferencing: " << endl;
    int i = 0;
    while (*(textPtr + i) != '\0' && i < 10) { // Only show up to 10 chars
        cout << "*(textPtr + " << i << ") = '" << *(textPtr + i) << "'" << endl;
        i++;
    }// display each character using pointer dereferencing
    
    if (*(textPtr + i) != '\0') {
        cout << "... (more characters follow)" << endl;
    } // display if there are more characters
    
    cout << "\nThe dereference operator (*) allows you to:" << endl;
    cout << "1. Access the value at the memory address stored in a pointer" << endl;
    cout << "2. Modify the value at that memory address" << endl;
    cout << "This is a powerful feature that enables indirect manipulation of variables." << endl;
}

void demonstrateStructPointers() {
    cout << "\n=== Pointers with User-Defined Structs ===" << endl;
    cout << "The asterisk (*) operator is particularly useful with structs and can be used" << endl;
    cout << "to access struct members indirectly through pointers." << endl;
    cout << "Syntax: structPointer->memberName or (*structPointer).memberName" << endl << endl;
    
    // Create a Person struct
    Person person;
    
    // Get user input for the struct
    clearInputBuffer();
    cout << "Enter a name: ";
    cin.getline(person.name, 50);
    
    cout << "Enter age: ";
    cin >> person.age;
    
    cout << "Enter height (in meters): ";
    cin >> person.height;
    
    // Create a pointer to the struct
    Person *personPtr = &person;

    cout << "Person person = {" << person.name << ", " << person.age << ", " << person.height << "}" << endl;// display struct values
    
    // Accessing struct members directly
    cout << "Accessing struct members directly:" << endl;
    cout << "person.name: " << person.name << endl;
    cout << "person.age: " << person.age << endl;
    cout << "person.height: " << person.height << endl << endl;
    
    // Accessing struct members through pointer using arrow operator (->)
    cout << "Accessing struct members through pointer using arrow operator (->):" << endl;
    cout << "personPtr->name: " << personPtr->name << endl;
    cout << "personPtr->age: " << personPtr->age << endl;
    cout << "personPtr->height: " << personPtr->height << endl << endl;
    
    // Accessing struct members through pointer using dereference and dot operators
    cout << "Accessing struct members through pointer using dereference and dot operators (*.): " << endl;
    cout << "(*personPtr).name: " << (*personPtr).name << endl;
    cout << "(*personPtr).age: " << (*personPtr).age << endl;
    cout << "(*personPtr).height: " << (*personPtr).height << endl << endl;
}// demonstrate struct pointers function

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}// clear input buffer function

void copyString(char* destination, const char* source) {
    int i = 0;
    while (source[i] != '\0') {
        destination[i] = source[i];
        i++;
    }
    destination[i] = '\0';
}

int stringLength(const char* str) {
    int length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}