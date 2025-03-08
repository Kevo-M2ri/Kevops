#include "pointer.h"
#include <iostream>
#include <limits>

using namespace std;

void displayMenu() {
    cout << "\n=== MENU ===" << endl;
    cout << "1. Arithmetic Multiplication Operator" << endl;
    cout << "2. Pointer Declaration Operator" << endl;
    cout << "3. Pointer Dereference (Indirection) Operator" << endl;
    cout << "4. Pointers with User-Defined Structs" << endl;
    cout << "5. Additional Resources" << endl;
    cout << "6. Quit" << endl;
}

void demonstrateMultiplication() {
    cout << "\n=== Arithmetic Multiplication Operator ===" << endl;
    cout << "In C++, the asterisk (*) is used for multiplication between two values." << endl;
    cout << "Syntax: result = operand1 * operand2;" << endl << endl;
    
    double num1, num2;
    cout << "Enter two numbers to multiply:" << endl;
    cout << "First number: ";
    cin >> num1;
    cout << "Second number: ";
    cin >> num2;
    
    double result = num1 * num2;
    
    cout << "\nExample:" << endl;
    cout << "double result = " << num1 << " * " << num2 << ";" << endl;
    cout << "Result: " << result << endl;
    
    cout << "\nThe multiplication operator can be used with integers, floating-point numbers," << endl;
    cout << "and any other numeric types in C++." << endl;
}

void demonstratePointerDeclaration() {
    cout << "\n=== Pointer Declaration Operator ===" << endl;
    cout << "The asterisk (*) is used to declare a pointer variable that stores the address of another variable." << endl;
    cout << "Syntax: dataType *pointerName;" << endl << endl;
    
    int userValue;
    cout << "Enter an integer value: ";
    cin >> userValue;
    
    // Create a pointer to the user's value
    int *ptr = &userValue;
    
    cout << "\nExample:" << endl;
    cout << "int userValue = " << userValue << ";" << endl;
    cout << "int *ptr = &userValue;" << endl << endl;
    
    cout << "Here, we have:" << endl;
    cout << "- userValue: " << userValue << " (the actual value)" << endl;
    cout << "- &userValue: " << &userValue << " (the memory address of userValue)" << endl;
    cout << "- ptr: " << ptr << " (the pointer stores the address of userValue)" << endl;
    cout << "- *ptr: " << *ptr << " (the value at the address stored in ptr)" << endl << endl;
    
    // Demonstrate with char array
    char name[50];
    clearInputBuffer();
    cout << "Enter your name: ";
    cin.getline(name, 50);
    
    char *namePtr = name; // Points to the first element
    
    cout << "\nExample with character array:" << endl;
    cout << "char name[50] = \"" << name << "\";" << endl;
    cout << "char *namePtr = name;" << endl << endl;
    
    cout << "Here, we have:" << endl;
    cout << "- name: " << name << " (the array contents)" << endl;
    cout << "- name: " << static_cast<void*>(name) << " (the memory address of the array)" << endl;
    cout << "- namePtr: " << static_cast<void*>(namePtr) << " (points to the same address)" << endl;
    cout << "- *namePtr: '" << *namePtr << "' (the first character of the array)" << endl;
    
    cout << "\nNote that the & symbol is the address-of operator, which returns the memory address" << endl;
    cout << "of a variable. It's often used together with the pointer declaration." << endl;
}

void demonstratePointerDereference() {
    cout << "\n=== Pointer Dereference (Indirection) Operator ===" << endl;
    cout << "Once a pointer is declared, the asterisk (*) is used to access the value stored" << endl;
    cout << "at the memory address contained in the pointer. This is called dereferencing." << endl;
    cout << "Syntax: value = *pointerName;" << endl << endl;
    
    int userValue;
    cout << "Enter an integer value: ";
    cin >> userValue;
    
    // Create a pointer to the user's value
    int *ptr = &userValue;
    
    cout << "\nExample:" << endl;
    cout << "int userValue = " << userValue << ";" << endl;
    cout << "int *ptr = &userValue;" << endl;
    cout << "*ptr = " << *ptr << ";" << endl << endl;
    
    // Modify the value through the pointer
    cout << "Let's modify the value using the pointer." << endl;
    cout << "Enter a new value: ";
    cin >> *ptr;
    
    cout << "\nAfter modifying:" << endl;
    cout << "*ptr = " << *ptr << ";" << endl;
    cout << "userValue = " << userValue << ";" << endl << endl;
    
    // Demonstrate with character array
    char text[50];
    clearInputBuffer();
    cout << "Enter a short sentence: ";
    cin.getline(text, 50);
    
    char *textPtr = text;
    
    cout << "\nExample with character array:" << endl;
    cout << "char text[50] = \"" << text << "\";" << endl;
    cout << "char *textPtr = text;" << endl << endl;
    
    // Display each character using pointer arithmetic
    cout << "Let's access each character using pointer dereferencing:" << endl;
    int i = 0;
    while (*(textPtr + i) != '\0' && i < 10) { // Only show up to 10 chars
        cout << "*(textPtr + " << i << ") = '" << *(textPtr + i) << "'" << endl;
        i++;
    }
    
    if (*(textPtr + i) != '\0') {
        cout << "... (more characters follow)" << endl;
    }
    
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
    
    cout << "\nExample:" << endl;
    cout << "struct Person {" << endl;
    cout << "    char name[50];" << endl;
    cout << "    int age;" << endl;
    cout << "    double height;" << endl;
    cout << "};" << endl << endl;
    
    cout << "Person person = {\"" << person.name << "\", " << person.age << ", " << person.height << "};" << endl;
    cout << "Person *personPtr = &person;" << endl << endl;
    
    cout << "Accessing struct members directly:" << endl;
    cout << "person.name: " << person.name << endl;
    cout << "person.age: " << person.age << endl;
    cout << "person.height: " << person.height << endl << endl;
    
    cout << "Accessing struct members through pointer using arrow operator (->):" << endl;
    cout << "personPtr->name: " << personPtr->name << endl;
    cout << "personPtr->age: " << personPtr->age << endl;
    cout << "personPtr->height: " << personPtr->height << endl << endl;
    
    cout << "Accessing struct members through pointer using dereference and dot operators (*.): " << endl;
    cout << "(*personPtr).name: " << (*personPtr).name << endl;
    cout << "(*personPtr).age: " << (*personPtr).age << endl;
    cout << "(*personPtr).height: " << (*personPtr).height << endl << endl;
    
    cout << "Note: personPtr->member is equivalent to (*personPtr).member" << endl;
    cout << "The arrow operator (->) is simply a more convenient syntax for accessing" << endl;
    cout << "struct members through a pointer." << endl;
}

void displayResources() {
    cout << "\n=== Additional Resources ===" << endl;
    cout << "Here are some resources to learn more about pointers and the asterisk operator in C++:" << endl;
    cout << "1. C++ Reference: https://en.cppreference.com/w/cpp/language/pointer" << endl;
    cout << "2. C++ Pointers Tutorial: https://www.learncpp.com/cpp-tutorial/pointers/" << endl;
    cout << "3. Video Tutorial: https://www.youtube.com/watch?v=DTxHyVn0ODg" << endl;
    cout << "4. Interactive C++ Course: https://www.learn-cpp.org/en/Pointers" << endl;
    cout << "5. Book: 'C++ Primer' by Stanley B. Lippman" << endl;
    
    cout << "\nRemember that pointers are a powerful but complex feature of C++." << endl;
    cout << "Practice is essential to master their use and avoid common pitfalls." << endl;
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

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