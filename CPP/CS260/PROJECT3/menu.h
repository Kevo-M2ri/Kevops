// menu.h
#pragma once

#include "table.h"

// Display the main menu
void displayMenu();

// Load student data from external file
bool loadFromFile(Table& table, const char* filename);

// Add a new student to the hash table
void addStudent(Table& table);

// Retrieve and display all students from a given program
void retrieveStudents(Table& table);

// Edit a student's academic standing
void editStudent(Table& table);

// Remove all students with unacceptable standing
void removeUnacceptable(Table& table);

// Clear input buffer
void clearInputBuffer();