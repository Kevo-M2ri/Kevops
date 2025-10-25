/*  Name: Kelvin Muturi
    class: CS260
    Project: project2
*/

#include "undoRedoManager.h"

const int MAX_LINE_LENGTH = 256;  // Maximum length for command descriptions

// Constructor: Initializes sequence number counter
UndoRedoManager::UndoRedoManager() : nextSequenceNumber(1) {}

// Loads commands from a text file
void UndoRedoManager::loadCommandsFromFile(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        // File not found: create a sample file
        std::cout << "Error: File " << filename << " not found" << std::endl;
        std::cout << "Creating sample file..." << std::endl;
        if (createSampleFile(filename)) {
            std::cout << "Sample file created successfully. Please run the program again." << std::endl;
        }
        return;
    }
    
    char line[MAX_LINE_LENGTH];
    int loadedCount = 0;
    
    // Read each line from the file
    while (file.getline(line, MAX_LINE_LENGTH)) {
        if (strlen(line) > 0) { // Skip empty lines
            // Add command to history with incrementing sequence number
            commandHistory.addToEnd(nextSequenceNumber, line);
            nextSequenceNumber++;
            loadedCount++;
        }
    }
    
    file.close();
    std::cout << "Loaded " << loadedCount << " commands from " << filename << std::endl;
}

// Displays the current command history
void UndoRedoManager::showCommandHistory() const {
    std::cout << "\n--- Command History ---" << std::endl;
    
    // Display undone commands (available for redo) at the top with indentation
    if (!undoStack.isEmpty()) {
        Command* current = undoStack.peekFront();
        while (current != nullptr) {
            std::cout << "     ";  // Indent undone commands
            current->display();
            current = current->next;
        }
    }
    
    // Display active command history
    commandHistory.display();
}

// Undoes the specified number of commands
void UndoRedoManager::undo(int numCommands) {
    if (commandHistory.isEmpty()) {
        std::cout << "No commands to undo" << std::endl;
        return;
    }
    
    // Undo at most the number of commands available
    int actualUndo = std::min(numCommands, commandHistory.getSize());
    std::cout << "Undoing " << actualUndo << " command(s)..." << std::endl;
    
    // Move commands from history to undo stack
    for (int i = 0; i < actualUndo; i++) {
        if (!commandHistory.isEmpty()) {
            Command* command = commandHistory.removeFromEnd();
            // Add to front of undo stack (LIFO for redo)
            undoStack.addToFront(command->sequenceNumber, command->description);
            delete command; // Clean up the removed command
        }
    }
    
    showCommandHistory();
}

// Redoes the specified number of commands
void UndoRedoManager::redo(int numCommands) {
    if (undoStack.isEmpty()) {
        std::cout << "No commands to redo" << std::endl;
        return;
    }
    
    // Redo at most the number of commands available
    int actualRedo = std::min(numCommands, undoStack.getSize());
    std::cout << "Redoing " << actualRedo << " command(s)..." << std::endl;
    
    // Move commands from undo stack back to history
    for (int i = 0; i < actualRedo; i++) {
        if (!undoStack.isEmpty()) {
            Command* command = undoStack.removeFromFront();
            // Add back to end of command history
            commandHistory.addToEnd(command->sequenceNumber, command->description);
            delete command; // Clean up the removed command
        }
    }
    
    showCommandHistory();
}

// Displays statistics about the command history
void UndoRedoManager::getStatistics() const {
    std::cout << "\n--- Statistics ---" << std::endl;
    std::cout << "Active commands: " << commandHistory.getSize() << std::endl;
    std::cout << "Undone commands available for redo: " << undoStack.getSize() << std::endl;
    std::cout << "Next sequence number: " << nextSequenceNumber << std::endl;
}

// Creates a sample commands file for testing
bool UndoRedoManager::createSampleFile(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error creating sample file!" << std::endl;
        return false;
    }
    
    // Array of sample commands
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
    
    // Write each command to the file
    for (int i = 0; sampleCommands[i] != nullptr; i++) {
        file << sampleCommands[i] << std::endl;
    }
    
    file.close();
    return true;
}