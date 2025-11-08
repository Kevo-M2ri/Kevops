#pragma once

#include "student.h"

class Table {
public:
    // Constructor
    Table(int size = 10);
    
    // Destructor
    ~Table();
    
    // Insert a new student by program
    bool insert(const char* program, const char* g_number, 
                const char* name, int standing);
    
    // Retrieve all students from a given program
    bool retrieve(const char* program, Student all_matches[], int& num_found);
    
    // Edit academic standing for a particular student
    bool edit(const char* program, const char* g_number, int new_standing);
    
    // Remove all students with unacceptable standing (standing == 1)
    int remove();
    
    // Display all students
    void displayAll() const;
    
    // Monitor hash table performance (display chain lengths)
    void monitor() const;

private:
    Node** table;       // Array of pointers to linked lists
    int table_size;     // Size of hash table
    
    // Hash function
    int hash(const char* key) const;
    
    // Helper function to delete a chain
    void deleteChain(Node*& head);
};