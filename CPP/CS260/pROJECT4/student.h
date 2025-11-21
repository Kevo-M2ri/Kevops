#pragma once

#include <cstring>

// Student structure to hold student information
struct Student {
    char* program;    // program name
    char* gNumber;    // student G Number (BST key)
    char* name;       // student name
    int standing;     // academic standing

    Student(); // constructor
    ~Student(); // destructor
    void copy(const Student& source);
    void clear();
    int compare(const char* otherGNumber) const;
};

// BST Node structure
struct BSTNode {
    Student data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(); // Constructor
    ~BSTNode(); // Destructor
};

// Convert standing to string
const char* standingToString(int standing);