/*  Name: Kelvin Muturi
    class: CS260
    Project: project2
*/

#pragma once

#include "deque.h"
#include <fstream>
#include <algorithm>

class UndoRedoManager {
private:
    Deque command_history;      // Main command history (rear = most recent)
    Deque undo_stack;           // Commands that have been undone (available for redo)
    int next_sequence_number;   // Counter for assigning sequence numbers

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
    void undo(int num_commands);
    
    // Redoes the specified number of commands
    void redo(int num_commands);
    
    // Displays statistics about the command history
    void getStatistics() const;
    
    // Utility
    
    // Creates a sample commands file for testing
    bool createSampleFile(const char* filename);
};