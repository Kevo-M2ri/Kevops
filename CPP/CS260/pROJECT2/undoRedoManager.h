#ifndef UNDOREDOMANAGER_H
#define UNDOREDOMANAGER_H

#include "deque.h"

class UndoRedoManager {
private:
    Deque command_history; // Main command history (rear = most recent)
    Deque undo_stack;      // Commands that have been undone (front = next to redo)
    int next_sequence_number;

public:
    UndoRedoManager();
    
    // File operations
    void loadCommandsFromFile(const char* filename);
    
    // Core functionality
    void showCommandHistory() const;
    void undo(int num_commands);
    void redo(int num_commands);
    void getStatistics() const;
    
    // Utility
    bool createSampleFile(const char* filename);
};

#endif