#include "engineerlist.h"

void displayMenu();
void getIntegerInput(const char* prompt, int min, int max);
AssessmentLevel getAssessmentInput();
// Main function
int main() {
    EngineerList engineers;
    const char* filename = "engineers.txt";

    // Load engineers from file
    cout << "Loading engineers from file: " << filename << "..." << endl;
    if (!engineers.loadFromFile(filename)) {
        cout << "Failed to load engineers from file: " << filename << endl;
        cout <<" Starting with an empty list." << endl;
    }
    else {
        cout << "Data loaded successfully." << endl;
    }

    int choice;
    do {
        displayMenu();
        choice = getIntegerInput("Enter your choice: ", 1, 8);

        switch (choice) {
            case 1: { // Add Engineer
                char firstName[50], lastName[50];
                int titleLevel;

                cout << "Enter first name: ";
                cin.getline(firstName, 50);
                cout << "Enter last name: ";
                cin.getline(lastName, 50);
                
                titleLevel = getIntegerInput("Enter title level", MIN_TITLE_LENGTH, MAX_TITLE_LENGTH);
                AssessmentLevel assessment = getAssessmentInput();

                Engineer* newEng = new Engineer(firstName, lastName, titleLevel, assessment);
                if (engineers.addEngineer(newEng)) {
                    cout << "Engineer added successfully." << endl;
                } else {
                    cout << "Failed to add engineer." << endl;
                    delete newEng; // Clean up if not added
                }
                break;
            }
            case 2: { // Promote Engineer
                if (engineers.getSize() == 0) {
                    cout << "No engineers to promote." << endl;
                    break;
                }
                int index = getIntegerInput("Enter engineer index to promote", 0, engineers.getSize() - 1);
                if (engineers.promoteEngineer(index)) {
                    cout << "Engineer promoted successfully." << endl;
                }
                else {
                    cout << "Failed to promote engineer." << endl;
                }
                break;
            }
            case 3: { // Edit Engineer Assessment
                if (engineers.getSize() == 0) {
                    cout << "No engineers to edit." << endl;
                    break;
                }

                cout << "Current Engineers:" << endl;
                engineers.displayAll();

                int index = getIntegerInput("Enter engineer index to edit assessment", 0, engineers.getSize() - 1);
                AssessmentLevel newAssessment = getAssessmentInput();

                if (engineers.editAssessment(index, newAssessment)) {
                    cout << "Engineer assessment updated successfully." << endl;
                }
                else {
                    cout << "Failed to update assessment." << endl;
                }
                break;
            }
            case 4: // Display All Engineers
                cout <<"All Engineers (sorted by name):" << endl;
                engineers.displayAll();
                break;

            case 5: { // Display Engineers by Title Level
                int level = getIntegerInput("Enter title level to display", MIN_TITLE_LENGTH, MAX_TITLE_LENGTH);
                engineers.displayByLevel(level);
                break;
            }
            case 6: { // Remove underPerforming Engineers
                int removed = engineers.removeByAssessment(UNACCEPTABLE);
                cout << "Removed " << removed << " engineers with unacceptable performance." << endl;
                break;
            }
            case 7: // Show Total Engineers Number
                cout << "Total number of engineers in list: " << engineers.getSize() << endl;
                break;
            case 8: // Exit
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        if (choice != 8) {
            cout << "Press Enter to continue...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cin.get();
        }
    }while (choice != 8);

    return 0;
}

// Display menu options
void displayMenu() {
    cout << "Engineer Management System Menu:" << endl;
    cout << "1. Add Engineer" << endl;
    cout << "2. Promote Engineer" << endl;
    cout << "3. Edit Engineer Assessment" << endl;
    cout << "4. Display All Engineers" << endl;
    cout << "5. Display Engineers by Title Level" << endl;
    cout << "6. Remove underPerforming Engineers" << endl;
    cout << "7. Show Total Engineers Number" << endl;
    cout << "8. Exit" << endl;
    cout << "Enter your choice: ";
}

// Get integer input with validation
int getIntegerInput(const char* prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt << " (" << min << "-" << max << "): ";
        cin >> value;

        if (cin.fail() || value < min || value > max) {
            cin.clear(); // Clear error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        }
        else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard any extra input
            return value;
        }
    }
}

// Get assessment level from user
AssessmentLevel getAssessmentInput() {
    cout << "Enter assessment Level:" << endl;
    cout << "1. Unacceptable" << endl;
    cout << "2. Needs Improvement" << endl;
    cout << "3. Meets Expectations" << endl;
    cout << "4. Exceeds Expectations" << endl;
    cout << "5. Outstanding" << endl;

    int choice = getIntegerInput("Choose the appropriate assessment level", 1, 5);
    return static_cast<AssessmentLevel>(choice);
}