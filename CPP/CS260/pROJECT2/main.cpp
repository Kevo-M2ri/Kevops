/*      Name: Kelvin Muturi
 *      Class: CS260
 *      Project: project2
*/

#include "undoRedoManager.h"

// minifunctions Prototypes
void displayMenu ();
int getIntegerInput ();

int main() {
	UndoRedoManager manager;

	cout << "Loading commands from file..." << endl;
	manager.loadCommandsFromFile("commands.txt");

	int choice;
	bool running = true;

	// Main program loop
	while (running) {
		displayMenu();
		choice = getIntegerInput("");

		switch (choice) {
			case 1://show command history
				manager.showCommandistory();
				break;

			case 2: { // undo commands
				int num = getIntegerInput("Enter number of commands to undo: ");
				if (num > 0) {
					manager.undo(num);
				}
				else {
					cout << "Please enter a positive number" << endl;
				}
				break;
			}

			case 3: { // redo commands
				int num = getIntegerInput("Enter number of commands to redo: ");
				if (num > 0) {
						manager.redo(num);
				}
				else {
					cout << "Please enter a positive number" << endl;
				}
				break;
			}

			case 4: //show statistics
				manager.getStatistics();
				break;

			case 5: //exit program
				cout << "Goodbye!" << endl;
				running = false;
				break;

			default: //invalid menu choice
				cout << "Invalid choice. Please try again." << endl;
			break;
		}
	}

	return 0;
}

// Display main menu options
void displayMenu() {
	cout << "\n=== Undo/Redo Manager ===" << endl;
    	cout << "1. Show command history" << endl;
    	cout << "2. Undo commands" << endl;
    	cout << "3. Redo commands" << endl;
    	cout << "4. Show statistics" << endl;
    	cout << "5. Exit" << endl;
     	cout << "Enter your choice (1-5): ";
}

int getIntegerInput (const char* prompt) {
	int value;
	while (true) {
		cout << prompt;
		cin >> value;

		if (cin.fail()) {
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Invalid input. Please enter a number." << endl;
		}
		else {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return value;
		}
	}
}
