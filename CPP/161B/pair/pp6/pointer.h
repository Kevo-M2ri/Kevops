#ifndef POINTER_USE_H
#define POINTER_USE_H

// Define a user-defined struct for demonstrating pointers with structs
struct Person {
    // Define the struct members
    char name[50];
    int age;
    double height;
};

// Function prototypes
void displayMenu();
void demonstrateMultiplication();
void demonstratePointerDeclaration();
void demonstratePointerDereference();
void demonstrateStructPointers();
void clearInputBuffer();
void copyString(char* destination, const char* source);
int stringLength(const char* str);

#endif // POINTER_USE_H