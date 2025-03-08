#ifndef POINTER_USE_H
#define POINTER_USE_H

// Define a user-defined struct for demonstrating pointers with structs
struct Person {
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
void displayResources();
void clearInputBuffer();

// Helper functions for char arrays
void copyString(char* destination, const char* source);
int stringLength(const char* str);

#endif // POINTER_USE_H