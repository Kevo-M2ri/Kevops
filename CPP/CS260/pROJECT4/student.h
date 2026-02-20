<<<<<<< HEAD
/*********************************
 * Kelvin Muturi
 * CS260 Fall25
 * Project4
 *********************************/

#pragma once

#include <cstring>
#include <iostream>

using namespace std;

// Student structure to hold student information
struct Student {
	char* program; // program name
	char* gNumber; // student G Number
	char* name; // student number
	int standing; // academic standing

	Student(); // constructor
	~Student(); //destructor
	void copy(const Student& source);
	void clear();
	int compare(const char* otherGNumber) const;
=======
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
>>>>>>> 8b805a66d5e637f07d1516c9f5fc3c970359721c
};

// BST Node structure
struct BSTNode {
<<<<<<< HEAD
	Student data;
	BSTNode* left;
	BSTNode* right;

	BSTNode(); // Constructor
	~BSTNode(); // Destructor
};

// Conver standing to string
const char* standingToString(int standing);
=======
    Student data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(); // Constructor
    ~BSTNode(); // Destructor
};

// Convert standing to string
const char* standingToString(int standing);
>>>>>>> 8b805a66d5e637f07d1516c9f5fc3c970359721c
