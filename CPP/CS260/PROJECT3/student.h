#pragma once

// Student structure to hold student information
struct Student {
    char* program;      // Program name (dynamically allocated)
    char* g_number;     // Student G# (dynamically allocated)
    char* name;         // Student name (dynamically allocated)
    int standing;       // Academic standing (1-5)
    
    // Constructor
    Student();
    
    // Destructor
    ~Student();
    
    // Copy student data
    void copy(const Student& source);
    
    // Clear student data
    void clear();
};

// Node structure for linked list in hash table
struct Node {
    Student data;
    Node* next;
    
    // Constructor
    Node();
    
    // Destructor
    ~Node();
};

// Helper function to convert standing to string
const char* standingToString(int standing);