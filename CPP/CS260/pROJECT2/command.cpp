/*  Name: Kelvin Muturi
    class: CS260
    Project: project2
*/

#include "command.h"

// Constructor: Allocates memory and copies the description string
Command::Command(int seq, const char* desc) : sequence_number(seq), next(nullptr), prev(nullptr) {
    // Allocate memory for description (strlen + 1 for null terminator)
    description = new char[strlen(desc) + 1];
    strcpy(description, desc);
}

// Destructor: Deallocates the dynamically allocated description
Command::~Command() {
    delete[] description;
}

// Copy constructor: Creates a deep copy of the command
Command::Command(const Command& other) : sequence_number(other.sequence_number), next(nullptr), prev(nullptr) {
    // Allocate new memory and copy the description
    description = new char[strlen(other.description) + 1];
    strcpy(description, other.description);
}

// Assignment operator: Performs deep copy with self-assignment check
Command& Command::operator=(const Command& other) {
    if (this != &other) {
        // Free existing memory
        delete[] description;
        
        // Copy sequence number
        sequence_number = other.sequence_number;
        
        // Allocate new memory and copy description
        description = new char[strlen(other.description) + 1];
        strcpy(description, other.description);
    }
    return *this;
}

// Display: Outputs the command in a readable format
void Command::display() const {
    std::cout << sequence_number << ". " << description << std::endl;
}