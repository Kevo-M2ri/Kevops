#pragma once

#include "student.h"
#include <iostream>
#include <cstring>

class Table {
public:
	Table(int size = 10);// Constructor
	~Table();// Destructor
	
	// Methods prototypes
	bool insert(const char* program, const char* gNumber, const char* name, int standing);
	bool retrieve(const char* program, Student allMatches[], int& numFound);
	bool edit(const char* program, const char* gNumber, int newStanding);
	int remove();
	void displayAll() const;
	void monitor() const;

private:
	//private attributes and methods
	Node** table;
	int tableSize;
	int hash(const char* key) const;
	void deleteChain(Node*& head);
};
