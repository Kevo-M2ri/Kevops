#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <cstring>
#include <limits>
#include <fstream>
#include <algorithm>

class Command {
public:
    int sequence_number;
    char* description;
    Command* next;
    Command* prev;
    
    Command(int seq, const char* desc);
    ~Command();
    Command(const Command& other); // Copy constructor
    Command& operator=(const Command& other); // Assignment operator
    void display() const;
};

#endif