/*      Name: Kelvin Muturi
 *      Class: CS260
 *      Project: project2
*/

#pragma once

#include "deque.h"

class UndoRedoManager {
private:
	// private attributes
	Deque commandHistory; // Main command history
	Deque undoStack; 
	int nextSequenceNumber;

public:
	// public methods
	undoRedoManager();
	void loadCommandsFromFile(const char* filename);
	void showCommandHistory() const;
	void undo(int numCommands);
	void redo(int numCommands);
	void getStatistics() const;
	bool createSampleFile(const char* fileName);
};
