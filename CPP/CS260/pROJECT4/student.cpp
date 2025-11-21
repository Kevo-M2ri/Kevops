#include "student.h"
#include <iostream>

using namespace std;

// Student constructor
Student::Student() : program(nullptr), gNumber(nullptr), name(nullptr), standing(0) {}

// Student destructor
Student::~Student() {
    clear();
}

// Copy student data
void Student::copy(const Student& source) {
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
BSTNode::BSTNode() : left(nullptr), right(nullptr) {}

// BST Node destructor
BSTNode::~BSTNode() {}

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