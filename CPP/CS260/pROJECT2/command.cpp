/*      Name: Kelvin Muturi
 *      Class: CS260
 *      Project: project2
*/

#include "command.h"

// Constructor method
Command::Command(int seq, const char* desc) : sequenceNumber(seq), next(nullptr), prev(nullptr) {
	description = new char[strlen(desc) + 1];// Allocation memory for description
	strcpy(description, desc);
}

// Destructor method
Command::~Command() {
	delete[] description;
}

// copy Constructor
Command::Command(const Command& other) : sequenceNumber(other.sequenceNumber), next(nullptr), prev(nullptr) {
	description = new char[strlen(other.description) + 1];// allocate new memory
	strcpy(description, other.description);// copy the description
}

// Assignment operator
Command& Command::operator=(const Command& other) {
	if (this != &other) {
		delete[] description;// free existing memory

		sequenceNumber = other.sequenceNumber;// copy sequence number

		description = new char[strlen(other.description) + 1];// allocate new memory
		strcpy(description, other.description);// copy description
	}
	return* this;
}

// Display command in readable format
void Command::display() const {
	cout << sequenceNumber << ". " << description << endl;
}

