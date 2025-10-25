/*  Name: Kelvin Muturi
    class: CS260
    Project: project2
*/

#pragma once

#include "deque.h"

class UndoRedoManager {
private:
    Deque commandHistory;       // Main command history (rear = most recent)
    Deque undoStack;            // Commands that have been undone (available for redo)
    int nextSequenceNumber;     // Counter for assigning sequence numbers

public:
    // Constructor: Initializes the manager
    UndoRedoManager();
    
    // File operations
    
    // Loads commands from a text file
    void loadCommandsFromFile(const char* filename);
    
    // Core functionality
    
    // Displays the current command history with undone commands indented
    void showCommandHistory() const;
    
    // Undoes the specified number of commands
    void undo(int numCommands);
    
    // Redoes the specified number of commands
    void redo(int numCommands);
    
    // Displays statistics about the command history
    void getStatistics() const;
    
    // Utility
    
    // Creates a sample commands file for testing
    bool createSampleFile(const char* filename);
};