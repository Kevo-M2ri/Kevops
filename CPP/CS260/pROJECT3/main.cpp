#include "table.h"
#include "menu.h"
#include <iostream>

using namespace std;

int main() {
	Table table(10);// Create hash table with size 10
	bool dataLoaded = false;

	//Display program header
	cout << "==================================" << endl;
	cout << "Student Academic Standing Tracker" << endl;
	cout << "==================================" << endl;

	//Load data from file
	cout << "\nLoading data from file..." << endl;
	if (loadFromFile(table, "students.txt")) {
		cout << "Data loaded successfully!" << endl;
		dataLoaded = true;
	}
	else {
		cout << "No data file found or file is empty. Starting with empty database." << endl;
		cout << "You can load data manually using option 7." << endl;
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
				addStudent(table);
				break;		
			case 2:
				retrieveStudents(table);
				break;
			case 3:
				editStudent(table);
				break;
			case 4:
				removeUnacceptable(table);
				break;
			case 5:
				table.displayAll();
				break;
			case 6:
				table.monitor();
				break;
			case 7:
				loadDataFromFile(table);
				dataLoaded = true;
				break;
			case 8:
				cout << "\nThank you for using the Student Tracker!" << endl;
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
