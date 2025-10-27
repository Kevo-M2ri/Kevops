/*      Name: Kelvin Muturi
 *      Class: CS260
 *      Project: project2
*/

#include "undoRedoManager.h"

const int MAX_LINE_LENGTH = 256; // Maximum length for command descriptions

// Constructor
UndoRedoManager::UndoRedoManager() : nextSequenceNumber(1) {}

// Read from a text file
void UndoRedoManager::loadCommandsFromFile(const char* filename) {
	ifstream file(filename);
	if (!file.is_open()) {
		// File not found, create a sample
		cout << "Error: File " << filename << " not found" << endl;
		cout <<"Creating sample file.. " << endl;
		if (createSampleFile(filename)) {
			cout << "Sample file created successfully. Please run the program again." << endl;
		}
		return;
	}

	char line[MAX_LINE_LENGTH];
	int loadedCount = 0;

	// read each line from 
	while (file.getline(line, MAX_LINE_LENGTH)) {
		if (strlen(line) > 0 ) {
			commandHistory.addToEnd(nextSequencenumber, line);
			nextSequenceNumber++;
			loadedCount++;
		}
	}

	file.close;
	cout << "Loaded " << loadedCount << " commands from " << filename << endl;
}

// Display the current command history
void UndoRedoManager::showCommandHistory() const {
	cout << "\n--- Command History ---" << endl;

	//display undone commands at the top with indentation
	if (!undoStack.isEmpty()) {
		Command* current = undoStack.peekFront();
		while (current != nullptr) {
			cout << "    ";// Indent undone commands
			current->display();
			current = current->next;
		}
	}

	commandHistory.display();//display active command history
}

// Undo the specified number of commands
void UndoRedoManager::undo(int numCommands) {
	if (commandHistory.isEmpty()) {
		cout << "No commands to undo" << endl;
		return;
	}

	//restrict undo to max number of commands available
	int actualUndo = min(numCommands, commandHistory.getSize());
	std::cout << "Undoing " << actualUndo << " command(s)..." << std::endl;

	for (int i = 0; i < actualUndo; i++) {
		if (!commandHistory.isEmpty()) {
			Command* command = commandHistory.removeFromEnd();
			undoStack.addToFront(command->sequenceNumber, command->description);
			delete command;
		}
	}
	showCommandHistory();
}

//Redo the specifies number of commands
void undoRedoManager::redo(int numCommands) {
	if (undoStack isEmpty()) {
		cout << "No commands to redo" << endl;
		return;
	}

	// restrict redo to the most number of commands available
	int actualRedo = min(numCommands, undoStack.getSize());
	cout << "Redoing " << actualRedo << command(s)..." << std::endl;

	for(int i = 0; i < actualRedo; i++) {
		if (!undoStack.isEmpty()) {
			Command* command = undoStack.removeFromFront();
			commandHistory.addToEnd(command->sequenceNumber, command->description);
			delete command;// clean up the removed command
		}
	}

	showCommandHistory();
}

// Displays statistics about the command history
void UndoRedoManager::gteStatistics() const {
	cout <<"\n--- Statistics ---" << endl;
	cout << "Active commands: " << commandHistory.getsize() << endl;
	cout << "Undone commands available for redo: " << undoStack.getSize() << endl;
	cout << "Next sequence number: " << nextSequenceNumber << endl;
}

// Creates a sample commands file for testing
bool UndoRedoManager::createSampleFile(const char* filename) {
	ofstream file(filename);
	if (!file.is_open()) {
		cout << "Error creating sample file!" << endl;
		return false;
	}

	const char* sampleCommands[] = {
		"copy line 3-6",
		"paste line 3-6 after line 10",
	        "remove line 20-30",
        	"remove the first 3 words of line 1",
	        "join line 20 and 30",
        	"replace all occurrences of \"num\" to \"number\"",
	        "comment out line 4-5",
        	"indent line 12-15",
	        "unindent line 5-8",
        	"uncomment line 9-11",
	        nullptr // Sentinel value to mark end of array
	};

	// write each command to file
	for (int i = 0; sampleCommands[i] != nullptr; i++) {
		file << sampleCommands[i] << endl;
	}

	file.close();
	return true;
}
