#include "menu.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

// Display main menu
void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "          BST STUDENT TRACKER" << endl;
    cout << "========================================" << endl;
    cout << "1. Add a new student" << endl;
    cout << "2. Retrieve student by G number" << endl;
    cout << "3. Edit student's academic standing" << endl;
    cout << "4. Remove a student by G number" << endl;
    cout << "5. Remove all students in a program" << endl;
    cout << "6. Display all students (sorted by G#)" << endl;
    cout << "7. Monitor BST performance" << endl;
    cout << "8. Load data from file" << endl;
    cout << "9. Exit" << endl;
    cout << "======================================" << endl;
}

// Load student data from external file
bool loadFromFile(BST& tree, const char* filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Cannot open file!! '" << filename << "'" << endl;
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
        
        if (tree.insert(program, gNumber, name, standing)) {
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
void loadDataFromFile(BST& tree) {
    char filename[100];

    cout << "\n===== LOAD DATA FROM FILE =====" << endl;
    cout << "Enter filename (default: students.txt): ";
    cin.getline(filename, 100);
    
    // Use default if empty
    if (strlen(filename) == 0) {
        strcpy(filename, "students.txt");
    }
    
    if (loadFromFile(tree, filename)) {
        cout << "Data loaded successfully!" << endl;
    }
    else {
        cout << "Failed to load data from " << filename << endl;
        cout << "Please check if the file exists and is formatted correctly." << endl;
        cout << "Expected format: program,g_number,name,standing" << endl;
    }
}

// Add a new student to the BST
void addStudent(BST& tree) {
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
    cin.getline(name, 100);

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

    if (tree.insert(program, gNumber, name, standing)) {
        cout << "\nStudent added successfully!" << endl;
    }
    else {
        cout << "\nFailed to add student. G number might already exist." << endl;
    }
}

// Retrieve and display a student by G number
void retrieveStudent(BST& tree) {
    char gNumber[20];
    Student result;

    cout << "\n===== RETRIEVE STUDENT =====" << endl;
    cout << "Enter student G number: ";
    cin.getline(gNumber, 20);

    if (tree.retrieve(gNumber, result)) {
        cout << "\nStudent found:" << endl;
        cout << "======================================" << endl;
        cout << "Program: " << result.program << endl;
        cout << "G#: " << result.gNumber << endl;
        cout << "Name: " << result.name << endl;
        cout << "Standing: " << standingToString(result.standing) << endl;
        cout << "--------------------------------------" << endl;
    }
    else {
        cout << "\nStudent not found: " << gNumber << endl;
    }
}

// Edit a student's academic standing
void editStudent(BST& tree) {
    char gNumber[20];
    int newStanding;

    cout << "\n====== EDIT STUDENT STANDING ======" << endl;
    cout << "Enter student G#: ";
    cin.getline(gNumber, 20);

    // First retrieve the student to get current info
    Student currentStudent;
    if (!tree.retrieve(gNumber, currentStudent)) {
        cout << "Student not found: " << gNumber << endl;
        return;
    }

    cout << "Current standing: " << standingToString(currentStudent.standing) << endl;
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

    // Remove and reinsert with updated standing
    if (tree.removeByGNumber(gNumber)) {
        if (tree.insert(currentStudent.program, currentStudent.gNumber, currentStudent.name, newStanding)) {
            cout << "\nStudent's standing updated successfully!" << endl;
        } else {
            // Reinsert with old standing if update fails
            tree.insert(currentStudent.program, currentStudent.gNumber, currentStudent.name, currentStudent.standing);
            cout << "\nUpdate failed. Please try again." << endl;
        }
    } else {
        cout << "\nStudent not found or update failed." << endl;
    }
}

// Remove a student by G number
void removeStudentByGNumber(BST& tree) {
    char gNumber[20];

    cout << "\n===== REMOVE STUDENT BY G NUMBER =====" << endl;
    cout << "Enter student G number to remove: ";
    cin.getline(gNumber, 20);

    cout << "Are you sure you want to remove student " << gNumber << "? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y') {
        if (tree.removeByGNumber(gNumber)) {
            cout << "\nStudent removed successfully!" << endl;
        } else {
            cout << "\nStudent not found or removal failed." << endl;
        }
    } else {
        cout << "\nOperation cancelled." << endl;
    }
}

// Remove all students in a program
void removeStudentsByProgram(BST& tree) {
    char program[100];

    cout << "\n===== REMOVE STUDENTS BY PROGRAM =====" << endl;
    cout << "Enter program name: ";
    cin.getline(program, 100);

    cout << "Are you sure you want to remove ALL students in " << program << "? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInputBuffer();

    if (confirm == 'y' || confirm == 'Y') {
        int count = tree.removeByProgram(program);
        cout << "\nRemoved " << count << " student(s) from " << program << endl;
    } else {
        cout << "\nOperation cancelled." << endl;
    }
}

// Clear input buffer
void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}