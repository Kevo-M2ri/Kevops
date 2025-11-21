/*********************************
 * Kelvin Muturi
 * CS260 Fall25
 * Project4
 *********************************/

#include "menu.h"

int main () {
	BST tree; //create bst
	bool dataLoaded = false;

	//Program banner
	cout << "===============================================" << endl;
	cout << "     BST Student Academic Standing Tracker     " << endl;
	cout << "===============================================" << endl;

	//Load data from file
	cout << "\nLoading data from file..." << endl;
	if (loadFromFile(tree, "students.txt")) {
		cout << "Data loaded successfully!" << endl;
		dataLoaded = true;
	}
	else {
		cout << "No data file found or file is empty. Starting with empty database." << endl;
		cout << "You can load data manually using option 8." << endl;
	}

	int choice;
	bool running = true;
	while (running) {
		displayMenu();
		cout << "Enter your choice: ";
		cin >> choice;
		clearInputBuffer();

		switch (choice) {
			case 1:
				addStudent(tree);
				break;
			case 2:
				retrieveStudent(tree);
				break;
			case 3:
				editStudent(tree);
				break;
			case 4:
				removeStudentByGNumber(tree);
				break;
			case 5:
				removeStudentsByProgram(tree);
				break;
			case 6:
				tree.displayAll();
				break;
			case 7:
				tree.monitor();
				break;
			case 8:
				loadDataFromFile(tree);
				dataLoaded = true;
				break;
			case 9:
				cout << "\nThank you for using the BST Student Tracker!" << endl;
				running = false;
				break;
			default:
				cout << "\nInvalid choice. Please try again!";
				cin.get();
		}

		if (running) {
			cout << "\nPress Enter to continue...";
			cin.get();
		}
	}

	return 0;
}
