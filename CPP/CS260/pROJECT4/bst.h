/*********************************
 * Kelvin Muturi
 * CS260 Fall25
 * Project4
 *********************************/

#pragma once

#include "student.h"
#include <cmath>

class BST {
public:
	BST(); // Constructor
	~BST(); // Destructor

	//Public interface methods
	bool insert(const char* program, const char* gNumber, const char* name, int standing);
	bool removeByGNumber(const char* gNumber);
	int removeByProgram(const char* program);
	bool retrieve(const char* gNumber, Student& result) const;
	void displayAll() const;
	void monitor() const;
	int getHeight() const;
	int getCount() const;
	bool isEmpty() const;

private:
	BSTNode* root;
	int nodeCount;

	// Private recursive methods
	BSTNode* insertRecursive(BSTNode* node, const char* program, const char* gNumber, const char* name, int standing);
	BSTNode* removeByGNumberRecursive(BSTNode* node, const char* gNumber, bool& success);
	int removeByProgramRecursive(BSTNode*& node, const char* program);
	bool retrieveRecursive(BSTNode* node, const char* gNumber, Student& result) const;
	void displayInOrder(BSTNode* node) const;
	void destroyTree(BSTNode* node);
	int getHeightRecursive(BSTNode* node) const;
	BSTNode* findMin(BSTNode* node) const;
};
