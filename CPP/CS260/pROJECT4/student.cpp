<<<<<<< HEAD
/*********************************
 * Kelvin Muturi
 * CS260 Fall25
 * Project4
 *********************************/

#include "student.h"
=======
#include "student.h"
#include <iostream>

using namespace std;
>>>>>>> 8b805a66d5e637f07d1516c9f5fc3c970359721c

// Student constructor
Student::Student() : program(nullptr), gNumber(nullptr), name(nullptr), standing(0) {}

// Student destructor
Student::~Student() {
<<<<<<< HEAD
	clear();
=======
    clear();
>>>>>>> 8b805a66d5e637f07d1516c9f5fc3c970359721c
}

// Copy student data
void Student::copy(const Student& source) {
<<<<<<< HEAD
	clear();

	if (source.program) {
		program = new char[strlen(source.program) + 1];
		strcpy(program, source.program);
	}

	if (source.gNumber) {
		gNumber = new char[strlen(source.gNumber) + 1];
		strcpy(gNumber, source.gNumber);
	}

	if (source.name) {
		name = new char[strlen(source.name) + 1];
		strcpy(name, source.name);
	}

	standing = source.standing;
}

// clear student data
void Student::clear() {
	delete[] program;
	delete[] gNumber;
	delete[] name;
	program = nullptr;
	gNumber = nullptr;
	name = nullptr;
	standing = 0;
}


// Compare G numbers for BST ordering
int Student::compare(const char* otherGNumber) const {
	return strcmp(gNumber, otherGNumber);
}

// BST Node Constructor
=======
    clear();

    if (source.program) {
        program = new char[strlen(source.program) + 1];
        strcpy(program, source.program);
    }

    if (source.gNumber) {
        gNumber = new char[strlen(source.gNumber) + 1];
        strcpy(gNumber, source.gNumber);
    }

    if (source.name) {
        name = new char[strlen(source.name) + 1];
        strcpy(name, source.name);
    }

    standing = source.standing;
}

// Clear student data
void Student::clear() {
    delete[] program;
    delete[] gNumber;
    delete[] name;
    program = nullptr;
    gNumber = nullptr;
    name = nullptr;
    standing = 0;
}

// Compare G numbers for BST ordering
int Student::compare(const char* otherGNumber) const {
    return strcmp(gNumber, otherGNumber);
}

// BST Node constructor
>>>>>>> 8b805a66d5e637f07d1516c9f5fc3c970359721c
BSTNode::BSTNode() : left(nullptr), right(nullptr) {}

// BST Node destructor
BSTNode::~BSTNode() {}

<<<<<<< HEAD
// convert standing to string
const char* standingToString (int standing) {
	switch(standing) {
		case 1: return "Unacceptable";
		case 2: return "Needs improvement";
		case 3: return "Meets expectations";
		case 4: return "Exceeds expectations";
		case 5: return "Outstanding";
		default: return "UNKNOWN!";
	}
}
=======
// Convert standing to string
const char* standingToString(int standing) {
    switch(standing) {
        case 1: return "Unacceptable";
        case 2: return "Needs improvement";
        case 3: return "Meets expectations";
        case 4: return "Exceeds expectations";
        case 5: return "Outstanding";
        default: return "UNKNOWN!";
    }
}
>>>>>>> 8b805a66d5e637f07d1516c9f5fc3c970359721c
