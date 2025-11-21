/*********************************
 * Kelvin Muturi
 * CS260 Fall25
 * Project4
 *********************************/

#pragma once

#include "bst.h"
#include <fstream>

//Menu functions
void displayMenu();
bool loadFromFile(BST& tree, const char* filename);
void addStudent(BST& tree);
void retrieveStudent(BST& tree);
void editStudent(BST& tree);
void removeStudentByGNumber(BST& tree);
void removeStudentsByProgram(BST& tree);
void loadDataFromFile(BST& tree);
void clearInputBuffer();
