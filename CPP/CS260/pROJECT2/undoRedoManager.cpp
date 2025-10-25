/*  Name: Kelvin Muturi
    class: CS260
    Project: project2
*/

#include "undoRedoManager.h"

const int MAX_LINE_LENGTH = 256;  // Maximum length for command descriptions

// Constructor: Initializes sequence number counter
UndoRedoManager::UndoRedoManager() : next_sequence_number(1) {}

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
    int loaded_count = 0;
    
    // Read each line from the file
    while (file.getline(line, MAX_LINE_LENGTH)) {
        if (strlen(line) > 0) { // Skip empty lines
            // Add command to history with incrementing sequence number
            command_history.addToEnd(next_sequence_number, line);
            next_sequence_number++;
            loaded_count++;
        }
    }
    
    file.close();
    std::cout << "Loaded " << loaded_count << " commands from " << filename << std::endl;
}

// Displays the current command history
void UndoRedoManager::showCommandHistory() const {
    std::cout << "\n--- Command History ---" << std::endl;
    
    // Display undone commands (available for redo) at the top with indentation
    if (!undo_stack.isEmpty()) {
        Command* current = undo_stack.peekFront();
        while (current != nullptr) {
            std::cout << "     ";  // Indent undone commands
            current->display();
            current = current->next;
        }
    }
    
    // Display active command history
    command_history.display();
}

// Undoes the specified number of commands
void UndoRedoManager::undo(int num_commands) {
    if (command_history.isEmpty()) {
        std::cout << "No commands to undo" << std::endl;
        return;
    }
    
    // Undo at most the number of commands available
    int actual_undo = std::min(num_commands, command_history.getSize());
    std::cout << "Undoing " << actual_undo << " command(s)..." << std::endl;
    
    // Move commands from history to undo stack
    for (int i = 0; i < actual_undo; i++) {
        if (!command_history.isEmpty()) {
            Command* command = command_history.removeFromEnd();
            // Add to front of undo stack (LIFO for redo)
            undo_stack.addToFront(command->sequence_number, command->description);
            delete command; // Clean up the removed command
        }
    }
    
    showCommandHistory();
}

// Redoes the specified number of commands
void UndoRedoManager::redo(int num_commands) {
    if (undo_stack.isEmpty()) {
        std::cout << "No commands to redo" << std::endl;
        return;
    }
    
    // Redo at most the number of commands available
    int actual_redo = std::min(num_commands, undo_stack.getSize());
    std::cout << "Redoing " << actual_redo << " command(s)..." << std::endl;
    
    // Move commands from undo stack back to history
    for (int i = 0; i < actual_redo; i++) {
        if (!undo_stack.isEmpty()) {
            Command* command = undo_stack.removeFromFront();
            // Add back to end of command history
            command_history.addToEnd(command->sequence_number, command->description);
            delete command; // Clean up the removed command
        }
    }
    
    showCommandHistory();
}

// Displays statistics about the command history
void UndoRedoManager::getStatistics() const {
    std::cout << "\n--- Statistics ---" << std::endl;
    std::cout << "Active commands: " << command_history.getSize() << std::endl;
    std::cout << "Undone commands available for redo: " << undo_stack.getSize() << std::endl;
    std::cout << "Next sequence number: " << next_sequence_number << std::endl;
}

// Creates a sample commands file for testing
bool UndoRedoManager::createSampleFile(const char* filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error creating sample file!" << std::endl;
        return false;
    }
    
    // Array of sample commands
    const char* sample_commands[] = {
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
    for (int i = 0; sample_commands[i] != nullptr; i++) {
        file << sample_commands[i] << std::endl;
    }
    
    file.close();
    return true;
}