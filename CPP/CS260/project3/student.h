#pragma once

#include <cstring>

// Student structure to hold student information
struct Student {
	char* program;// program name
	char* gNumber;// student G Number
	char* name;// student name
	int standing;// academic standing

	Student(); //constructor
	~Student(); //Destructor
	void copy(const Student& source);
	void clear();
};

//Node structure for linked list in hash table

struct Node {
	Student data;
	Node* next;

	Node(); // Constructor
	~Node(); // Destructor
};

// Convert standing to string
const char* standingToString(int standing);
