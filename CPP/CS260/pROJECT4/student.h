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
};

// BST Node structure
struct BSTNode {
	Student data;
	BSTNode* left;
	BSTNode* right;

	BSTNode(); // Constructor
	~BSTNode(); // Destructor
};

// Conver standing to string
const char* standingToString(int standing);
