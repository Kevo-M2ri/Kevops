<<<<<<< HEAD
/*********************************
 * Kelvin Muturi
 * CS260 Fall25
 * Project4
 *********************************/

#pragma once

#include "bst.h"
#include <fstream>

//Menu functions
=======
#pragma once

#include "bst.h"

// Menu functions
>>>>>>> 8b805a66d5e637f07d1516c9f5fc3c970359721c
void displayMenu();
bool loadFromFile(BST& tree, const char* filename);
void addStudent(BST& tree);
void retrieveStudent(BST& tree);
void editStudent(BST& tree);
void removeStudentByGNumber(BST& tree);
void removeStudentsByProgram(BST& tree);
void loadDataFromFile(BST& tree);
<<<<<<< HEAD
void clearInputBuffer();
=======
void clearInputBuffer();
>>>>>>> 8b805a66d5e637f07d1516c9f5fc3c970359721c
