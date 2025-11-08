#include "table.h"
#include <iostream>

using namespace std;

// Student constructor
Student::Student() : program(nullptr), gNumber(nullptr), name(nullptr), standing(0) {}

// Student destructor
Student::~Student() {
	clear();
}

// Copy student data
void Student::copy(const Student& source) {
	clear();

	if (source.program) {
		program = new char[strlen(source.program) + 1];
		strcpy(program, source.program);
	}

	if (source.gNumber) {
		gNumber = new char[strlen(source.gNumber) + 1];
		strcpy(gNumber, source.gNumber);
	}

	if (source.name) {
		name = new char[strlen(source.name) + 1];
		strcpy(name, source.name);
	}

	standing = source.standing;
}

// Clear student data
void Student::clear() {
	delete[] program;
	delete[] gNumber;
	delete[] name;
	program = nullptr;
	gNumber = nullptr;
	name = nullptr;
	standing = 0;
}

// Node constructor
Node::Node() : next(nullptr) {}

// Node destructor
Node::~Node() {}

// Convert standing to string
const char* standingToString(int standing) {
	switch(standing) {
		case 1: return "Unacceptable";
		case 2: return "Needs to improve";
		case 3: return "Meets expectations";
		case 4: return "Exceeds expectations";
		case 5: return "Outstanding";
		default: return "UNKNOWN!";
	}
}

// Table constructor
Table::Table(int size) : tableSize(size) {
	table = new Node*[tableSize];
	for (int i = 0; i < tableSize; ++i) {
		table[i] = nullptr;
	}
}

// Table destructor
Table::~Table() {
	for (int i = 0; i < tableSize; ++i) {
		deleteChain(table[i]);
	}
	delete[] table;
}

// Hash function
int Table::hash(const char* key) const {
	int sum = 0;
	for (int i = 0; key[i] != '\0'; ++i) {
		sum += key[i];
	}
	return sum % tableSize;
}

// Delete a chain
void Table::deleteChain(Node*& head) {
	while (head) {
		Node* temp = head;
		head = head->next;
		delete temp;
	}
}

// Insert a new student
bool Table::insert(const char* program, const char* gNumber, const char* name, int standing) {
	if (!program || !gNumber || !name || standing < 1 || standing > 5) {
		return false;
	}

	int index =  hash(program);

	// Create a new node
	Node* newNode = new Node();

	// Allocate and copy program
	newNode->data.program = new char[strlen(program) + 1];
	strcpy(newNode->data.program, program);

	// Allocate and copy gNumber
	newNode->data.gNumber = new char[strlen(gNumber) + 1];
	strcpy(newNode->data.gNumber, gNumber);

	// Allocate and copy name
	newNode->data.name = new char[strlen(name) + 1];
	strcpy(newNode->data.name, name);

	newNode->data.standing = standing;

	// Insert at beginning of chain
	newNode->next = table[index];
	table[index] = newNode;

	return true;
}

// Retrieve all students froma a given program
bool Table::retrieve(const char* program, Student allMatches[], int & numFound) {
	if (!program) {
		numFound = 0;
		return false;
	}

	int index = hash(program);
	Node* current = table[index];
	numFound = 0;

	while (current) {
		if (strcmp(current->data.program, program) == 0) {
			allMatches[numFound].copy(current->data);
			++numFound;
		}
		current = current->next;
	}

	return numFound > 0;
}

// Edit academic standing
bool Table::edit(const char* program, const char* gNumber, int newStanding) {
	if (!program || !gNumber || newStanding < 1 || newStanding > 5) {
		return false;
	}

	int index = hash(program);
	Node* current = table[index];

	while (current) {
		if (strcmp(current->data.program, program) == 0 && strcmp(current->data.gNumber, gNumber) == 0) {
			current->data.standing = newStanding;
			return true;
		}
		current = current->next;
	}
	return false;
}

// Remove all students with unacceptable standing
int Table::remove() {
	int count = 0;

	for (int i = 0; i < tableSize; ++i) {
		Node* current = table[i];
		Node* prev = nullptr;

		while (current) {
			if (current->data.standing == 1) {
				Node* toDelete = current;

				if (prev) {
					prev->next = current->next;
					current = current->next;
				}

				else {
					table[i] = current->next;
					current = table[i];
				}

				delete toDelete;
				++count;
			}
			
			else {
				prev = current;
				current = current->next;
			}
		}
	}

	return count;
}

// Display all students
void Table::displayAll() const {
	cout << "\n========= ALL STUDENTS IN PCC ============" << endl;
	int total = 0;

	for (int i = 0; i < tableSize; ++i) {
		Node* current = table[i];
		while (current) {
			cout << "\nProgram: " << current->data.program << endl;
			cout << "G#: " << current->data.gNumber << endl;
			cout << "Name: " << current->data.name << endl;
			cout << "Standing: " << standingToString(current->data.standing) <<endl;
			cout << "--------------------------------------" << endl;
			++total;
			current = current->next;
		}
	}
	
	cout << "\nTotal students: " << total << endl;
}

// Monitor hash table performance
void Table::monitor() const{
	cout << "===== HASH TABLE PERFORMANCE =====" << endl;
	cout << "Table size: " << tableSize << endl;
	cout << "\nChain Lengths: " << endl;

	int totalItems = 0;
	int usedSlots = 0;
	int maxChain = 0;

	for (int i = 0; i < tableSize; ++i) {
		int chainLength = 0;
		Node* current = table[i];

		while (current) {
			++chainLength;
			current = current->next;
		}

		if (chainLength > 0) {
			++usedSlots;
			cout << "Index " << i << ": " << chainLength << " item(s)" << endl;
		}

		totalItems += chainLength;
		if (chainLength > maxChain) {
			maxChain = chainLength;
		}
	}

	cout << "\nStatistics: " << endl;
	cout << "Total items: " << totalItems << endl;
	cout << "Used slots: " << usedSlots << " / " << tableSize << endl;
	cout << "Empty slots: " << (tableSize - usedSlots) << endl;
	cout << "Longest chain: " << maxChain << endl;

	if (usedSlots > 0) {
		cout << "Average chain length: " << (float)totalItems / usedSlots <<endl;
	}

	cout << "Load factor: " << (float)totalItems / tableSize << endl;
}
