#include "command.h"

Command::Command(int seq, const char* desc) : sequence_number(seq), next(nullptr), prev(nullptr) {
    // Allocate memory for description and copy the string
    description = new char[strlen(desc) + 1];
    strcpy(description, desc);
}

Command::~Command() {
    delete[] description;
}

// Copy constructor
Command::Command(const Command& other) : sequence_number(other.sequence_number), next(nullptr), prev(nullptr) {
    description = new char[strlen(other.description) + 1];
    strcpy(description, other.description);
}

// Assignment operator
Command& Command::operator=(const Command& other) {
    if (this != &other) {
        delete[] description;
        sequence_number = other.sequence_number;
        description = new char[strlen(other.description) + 1];
        strcpy(description, other.description);
    }
    return *this;
}

void Command::display() const {
    std::cout << sequence_number << ". " << description << std::endl;
}