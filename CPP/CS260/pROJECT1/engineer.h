#pragma once
#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

// Constants for title level
const int MAX_TITLE_LENGTH = 10;
const int MIN_TITLE_LENGTH = 2;

// Enumeration for assessment levels
enum AssessmentLevel {
    UNACCEPTABLE = 1,
    NEEDS_IMPROVEMENT = 2,
    MEETS_EXPECTATIONS = 3,
    EXCEEDS_EXPECTATIONS = 4,
    OUTSTANDING = 5
};

// Engineer class definition
class Engineer {
private: // Member variables
    char* fName;
    char* lName;
    int titleLevel;
    AssessmentLevel assessment;

    void copyString(char*& destination, const char* source); // Helper function to copy strings

public: // Member functions
    Engineer(const char* first, const char* last, int title, AssessmentLevel assess); // Constructor
    Engineer(const Engineer& other); // Copy constructor
    Engineer& operator=(const Engineer& other); // Copy assignment operator
    ~Engineer(); // Destructor

    const char* getFirstName() const {
        return fName;
    }; // Getter for first name
    const char* getLastName() const {
        return lName;
    }; // Getter for last name
    int getTitleLevel() const {
        return titleLevel;
    }; // Getter for title level
    AssessmentLevel getAssessment() const {
        return assessment;
    }; // Getter for assessment level
    const char* getAssessmentInfo() const; // Get assessment description

    void setFirstName(const char* first); // Setter for first name
    void setLastName(const char* last); // Setter for last name
    bool setTitleLevel(int title); // Setter for title level
    bool setAssessment(AssessmentLevel assess); // Setter for assessment level

    bool operator==(const Engineer& other) const; // Equality operator
    bool operator<(const Engineer& other) const; // Inequality operator

    void displayInfo() const; // Print engineer information
};