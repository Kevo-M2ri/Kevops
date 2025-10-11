#pragma once
#include "engineer.h"
#include <fstream>


using namespace std;

// Node structure for linked list
struct Node {
    Engineer data;
    Node* next;

    Node (Engineer eng) : data(eng), next(nullptr) {} // Constructor
    ~Node() { delete data; }// Destructor
};

// EngineerList class definition
class EngineerList {
private:
    Node* head; // Pointer to the head of the list
    Node* tail; // Pointer to the tail of the list
    int size; // Number of engineers in the list

    void clearList(); // Helper function to clear the list
    Node* findInsertionPoint(const Engineer& eng) const; // Helper function to find insertion point
    void removeByAssessmentRecursive(Node*& current, AssessmentLevel targetLevel); // Helper function for recursive removal
    void displayLevelRecursive(Node* current, int targetLevel) const; // Helper function for recursive display

public:
    EngineerList(); // Constructor
    EngineerList(const EngineerList& other); // Copy constructor
    EngineerList& operator=(const EngineerList& other); // assignment operator
    ~EngineerList(); // Destructor

    bool addEngineer(Engineer* eng); // Add engineer to the list
    bool promoteEngineer(int index); // Promote engineer at index
    bool editAssessment(int index, AssessmentLevel newLevel); // Edit assessment of engineer at index
    void displayAll() const; // Display all engineers
    void displayByLevel(int level) const; // Display engineers by title level
    int removeByAssessment(AssessmentLevel targetLevel); // Remove engineers by assessment level
    int getSize() const { return size; } // Get the size of the list
    const Engineer* getEngineerAt(int index) const; // Get engineer at index

    bool loadFromFile(const char* filename); // Load engineers from file
};