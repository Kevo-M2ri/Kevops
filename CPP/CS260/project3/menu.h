#pragma once

#include "table.h"

// Menu functions
void displayMenu();
bool loadFromFile(Table& table, const char* filename);
void addStudent(Table& table);
void retrieveStudents(Table& table);
void editStudent(Table& table);
void loadDataFromFile(Table& table);
void removeUnacceptable(Table& table);
void clearInputBuffer();
