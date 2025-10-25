/*  Name: Kelvin Muturi
    class: CS260
    Project: project2
*/

#pragma once

#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <limits>

class Command {
public:
    int sequenceNumber;         // Unique identifier for the command
    char* description;          // Dynamic string describing the command
    Command* next;              // Pointer to next command in the list
    Command* prev;              // Pointer to previous command in the list
    
    // Constructor: Creates a new command with sequence number and description
    Command(int seq, const char* desc);
    
    // Destructor: Frees dynamically allocated memory
    ~Command();
    
    // Copy constructor: Creates a deep copy of another command
    Command(const Command& other);
    
    // Assignment operator: Assigns one command to another with deep copy
    Command& operator=(const Command& other);
    
    // Display: Prints the command in format "seq. description"
    void display() const;
};