#include "menu.h"
#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

const int MAX_STUDENTS = 100;

// Display main menu
void displayMenu() {
	cout << "\n========================================" << endl;
	cout << "                MAIN MENU" << endl;
	cout << "========================================" << endl;
	cout << "1. Add a new student" << endl;
	cout << "2. Retrieve students by program" << endl;
	cout << "3. Edit student's academic standing" << endl;
	cout << "4. Remove students with unnacceptable standing" << endl;
	cout << "5. Display all students" << endl;
	cout << "6. Monitor hash table performance" << endl;
	cout << "7. Load data from file" << endl;
	cout << "8. Exit" << endl;
	cout << "======================================" << endl;
}

// Load student data from external file
bool loadFromFile(Table& table, const char* filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		cout << "Error: Cannot open file!! \'" << filename << "\'" << endl;
		return false;
	}

	char program[100];
	char gNumber[20];
	char name[100];
	int standing;
	int count = 0;
	int lineNumber = 0;

	cout << "Loading data from " << filename << "..." << endl;

	while (file.getline(program, 100, ',')) {
		lineNumber++;
		if (!file.getline(gNumber, 20, ',')) {
  			cout << "Warning: Incomplete data at line " << lineNumber << endl;
 			break;
		}
        
		if (!file.getline(name, 100, ',')) {
			cout << "Warning: Incomplete data at line " << lineNumber << endl;
			break;
		}
		
		file >> standing;
		if (file.fail()) {
			cout << "Warning: Invalid standing at line " << lineNumber << endl;
			file.clear();
			break;
		}
		
		file.ignore(100, '\n'); // Ignore the newline
		
		// Validate data before inserting
		if (strlen(program) == 0 || strlen(gNumber) == 0 || strlen(name) == 0) {
			cout << "Warning: Empty field at line " << lineNumber << endl;
			continue;
		}
		
		if (standing < 1 || standing > 5) {
			cout << "Warning: Invalid standing value " << standing << " at line " << lineNumber << endl;
			continue;
		}
		
		if (table.insert(program, gNumber, name, standing)) {
			++count;
		}
		else {
			cout << "Warning: Failed to insert student at line " << lineNumber << endl;
		}
		// Check for EOF
		if (file.eof()) {
			break;
		}
	}
	
	file.close();
	
	if (file.bad()) {
		cout << "Error: File read error occurred" << endl;
		return false;
	}
	
	cout << "Successfully loaded " << count << " student(s) from " << filename << endl;
	return count > 0;
}

// Load data from file
void loadDataFromFile(Table& table) {
	char filename[100];

	cout << "\n===== LOAD DATA FROM FILE =====" << endl;
	cout << "Enter filename (default: students.txt): ";
	cin.getline(filename, 100);
	
	// Use default if empty
	if (strlen(filename) == 0) {
		strcpy(filename, "students.txt");
	}
	
	if (loadFromFile(table, filename)) {
		cout << "Data loaded successfully!" << endl;
	}
	else {
		cout << "Failed to load data from " << filename << endl;
		cout << "Please check if the file exists and is formatted correctly." << endl;
		cout << "Expected format: program,g_number,name,standing" << endl;
	}
}

// Add a new student to the hash table
void addStudent(Table& table) {
	char program[100];
        char gNumber[20];
        char name[100];
        int standing;

	cout << "\n===== ADD NEW STUDENT =====" << endl;

	cout << "Enter program name: ";
	cin.getline(program, 100);

	cout << "Enter student G number: ";
	cin.getline(gNumber, 20);

	cout << "Enter student name: ";
	cin.getline(name,100);

	cout << "Enter academic standing (1-5):" << endl;
	cout << "  1 - Unacceptable" << endl;
	cout << "  2 - Needs improvement" << endl;
	cout << "  3 - Meets expectations" << endl;
	cout << "  4 - Exceeds expectations" << endl;
	cout << "  5 - Outstanding" << endl;
	cout << "Choice: ";
	cin >> standing;
	clearInputBuffer();

	if (standing < 1 || standing > 5) {
		cout << "\nInvalid standing. Must be between 1 and 5." << endl;
		return;
	}

	if (table.insert(program, gNumber, name, standing)) {
		cout << "\nStudent added successfully!" << endl;
	}
	else {
		cout << "\nFailed to add student." << endl;
	}
}

// Retrieve and display all students from a given program'
void retrieveStudents(Table& table) {
	char program[100];
	Student* matches = new Student[MAX_STUDENTS];
	int numFound = 0;

	cout << "\n===== RETRIEVE STUDENTS =====" << endl;
	cout << "Enter program name: ";
	cin.getline(program, 100);

	if (table.retrieve(program, matches, numFound)) {
		cout << "\nFound " << numFound << " student(s) in " << program << ":" << endl;
		cout << "======================================" << endl;

		for (int i = 0; i < numFound; ++i) {
			cout << "\n[" << (i + 1) << "]" << endl;
			cout << "G#: " << matches[i].gNumber << endl;
			cout << "Name: " << matches[i].name << endl;
			cout << "Standing " << standingToString(matches[i].standing) << endl;
			cout << "--------------------------" << endl;
		}
	}
	else {
		cout << "\nNo students found in program: " << program << endl;
	}

	delete[] matches;
}

// Edit a student's academic standing
void editStudent(Table& table) {
	char program[100];
	char gNumber[20];
	int newStanding;

	cout << "\n====== EDIT STUDENT STANDING ======" << endl;
	cout << "Enter program name: ";
	cin.getline(program, 100);
	
	cout << "Enter student G#: ";
	cin.getline(gNumber, 20);

	cout << "Enter new academic standing (1-5): " << endl;
	cout << "  1 - Unacceptable" << endl;
	cout << "  2 - Needs improvement" << endl;
	cout << "  3 - Meets expectations" << endl;
	cout << "  4 - Exceeds expectations" << endl;
	cout << "  5 - Outstanding" << endl;
	cout << "Choice: ";
	cin >> newStanding;
	clearInputBuffer();

	if (newStanding < 1 || newStanding > 5) {
		cout << "\nInvalid standing. Must be between 1 and 5." << endl;
		return;
	}

	if (table.edit(program, gNumber, newStanding)) {
		cout << "\nStudent's standing updated successfully!" << endl;
	}
	else {
		cout <<"\nStudent not found or update failed." << endl;
	}
}

// Remove all students with unacceptable standing
void removeUnacceptable(Table& table) {
	cout << "\n======== REMOVE UNACCEPTABLE STUDENTS =======" << endl;
	cout << "Are you sure you want to remove all students with unacceptable standing? (y/n): ";

	char confirm;
	cin >> confirm;
	clearInputBuffer();

	if (confirm == 'y' || confirm == 'Y') {
		int count = table.remove();
		cout << "\nRemoved " << count << " student(s) with unacceptable standing." << endl;
	}
	else {
		cout << "\nOperation cancelled." << endl;
	}
}

// Clear input buffer
void clearInputBuffer() {
	cin.clear();
	cin.ignore(10000, '\n');
}
