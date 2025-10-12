#include "engineer.h"

// Helper function to allocate and copy strings
void Engineer::copyString(char*& destination, const char* source) {
    delete[] destination; // Safe to delete nullptr

    if (source && source[0] != '\0') {
        destination = new char[strlen(source) + 1];
        strcpy(destination, source);
    }
    else {
        destination = new char[1];
        destination[0] = '\0';
    }
}
// Constructor
Engineer::Engineer(const char* first, const char* last, int title, AssessmentLevel assess)
    : fName(nullptr), lName(nullptr), titleLevel(title), assessment(assess) {
    setFirstName(first);
    setLastName(last);
}

// Copy constructor
Engineer::Engineer(const Engineer& other)
    : fName(nullptr), lName(nullptr), titleLevel(other.titleLevel), assessment(other.assessment) {
    setFirstName(other.fName);
    setLastName(other.lName);
}

// Assignment operator
Engineer& Engineer::operator=(const Engineer& other) {
    if (this != &other) {
        setFirstName(other.fName);
        setLastName(other.lName);
        titleLevel = other.titleLevel;
        assessment = other.assessment;
    }
    return *this;
}

// Destructor
Engineer::~Engineer() {
    delete[] fName;
    delete[] lName;
}

// Get assessment description
const char* Engineer::getAssessmentInfo() const {
    switch (assessment) {
        case UNACCEPTABLE:
            return "Unacceptable";
        case NEEDS_IMPROVEMENT:
            return "Needs Improvement";
        case MEETS_EXPECTATIONS:
            return "Meets Expectations";
        case EXCEEDS_EXPECTATIONS:
            return "Exceeds Expectations";
        case OUTSTANDING:
            return "Outstanding";
        default:
            return "Unknown";
    }
}

// Setters
void Engineer::setFirstName(const char* first) {
    copyString(fName, first);
}

void Engineer::setLastName(const char* last) {
    copyString(lName, last);
}

bool Engineer::setTitleLevel(int level) {
    if (level >= MIN_TITLE_LENGTH && level <= MAX_TITLE_LENGTH) {
        titleLevel = level;
        return true;
    }
    else {
        cerr << "Title level must be between " << MIN_TITLE_LENGTH << " and " << MAX_TITLE_LENGTH << "." << endl;
        return false;
    }
}

bool Engineer::setAssessment(AssessmentLevel assess) {
    if(assess >= UNACCEPTABLE && assess <= OUTSTANDING) {
        assessment = assess;
        return true;
    }
    else {
        cerr << "Invalid assessment level." << endl;
        return false;
    }
}

// Equality operator
bool Engineer::operator==(const Engineer& other) const {
    return strcmp(fName, other.fName) == 0 && strcmp(lName, other.lName) == 0;
}

// Inequality operator
bool Engineer::operator<(const Engineer& other) const {
    int lastNameComp = strcmp(lName, other.lName);
    if (lastNameComp < 0) return true;
    if (lastNameComp > 0) return false;
    return strcmp(fName, other.fName) < 0;
}

// Display engineer information
void Engineer::displayInfo() const {
    cout << "Engineer: " << fName << " " << lName << " - Level: L" << titleLevel
            << " - Assessment: " << getAssessmentInfo() << endl;
}