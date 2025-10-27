/*	Name: Kelvin Muturi
 *	Class: CS260
 *	Project: project2
*/

#pragma once

// header files
#include <iostream>
#include <cstring>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;

// class definition
class Command {
public:
	//class attributes
	int sequenceNumber;// Unique identifier for the command
	char* description;// command description string
	Command* next;// pointer to next command in the list
	Command* prev;// pointer to previous command in the list

	//Class Methods
	Command(int seq, const char* dec);
	~Command();
	Command(const Command& other);
	Command& operator=(const Command& other);
	void display() const;
};
