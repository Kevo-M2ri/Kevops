#include "undoRedoManager.h"

void displayMenu() {
    std::cout << "\n=== Undo/Redo Manager ===" << std::endl;
    std::cout << "1. Show command history" << std::endl;
    std::cout << "2. Undo commands" << std::endl;
    std::cout << "3. Redo commands" << std::endl;
    std::cout << "4. Show statistics" << std::endl;
    std::cout << "5. Exit" << std::endl;
    std::cout << "Enter your choice (1-5): ";
}

int getIntegerInput(const char* prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number." << std::endl;
        } else {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
    }
}

int main() {
    UndoRedoManager manager;
    
    // Load test data from file
    std::cout << "Loading commands from file..." << std::endl;
    manager.loadCommandsFromFile("commands.txt");
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        choice = getIntegerInput("");
        
        switch (choice) {
            case 1:
                manager.showCommandHistory();
                break;
                
            case 2: {
                int num = getIntegerInput("Enter number of commands to undo: ");
                if (num > 0) {
                    manager.undo(num);
                } else {
                    std::cout << "Please enter a positive number" << std::endl;
                }
                break;
            }
                
            case 3: {
                int num = getIntegerInput("Enter number of commands to redo: ");
                if (num > 0) {
                    manager.redo(num);
                } else {
                    std::cout << "Please enter a positive number" << std::endl;
                }
                break;
            }
                
            case 4:
                manager.getStatistics();
                break;
                
            case 5:
                std::cout << "Goodbye!" << std::endl;
                running = false;
                break;
                
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
    }
    
    return 0;
}