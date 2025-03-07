#include <iostream>
#include "mission.h"

using namespace std;

int main() {
    const int MAX_MISSIONS = 100;
    SpaceMission missions[MAX_MISSIONS];
    int missionCount = 0;
    int choice = 0;
    bool dataChanged = false;

    // Load missions from file
    missionCount = loadMissions(missions, MAX_MISSIONS);

    do {
        displayMenu();
        cout << "Enter your choice (1-6): ";
        cin >> choice;

        if (cin.fail() || !isValidChoice(choice, 1, 6)) {
            cout << "Invalid choice. Please enter a number between 1 and 6." << endl;
            clearInputBuffer();
        } else {
            switch (choice) {
                case 1: // Display all missions
                    displayMissions(missions, missionCount);
                    break;

                case 2: // Add a new mission
                    if (addMission(missions, missionCount, MAX_MISSIONS)) {
                        dataChanged = true;
                    }
                    break;

                case 3: // Find a mission
                    {
                        char searchTerm[50];
                        clearInputBuffer();
                        cout << "Enter search term: ";
                        cin.getline(searchTerm, 50);
                        findMissions(missions, missionCount, searchTerm);
                    }
                    break;

                case 4: // Remove a mission
                    {
                        char name[50];
                        clearInputBuffer();
                        cout << "Enter mission name to remove: ";
                        cin.getline(name, 50);
                        if (removeMission(missions, missionCount, name)) {
                            dataChanged = true;
                        }
                    }
                    break;

                case 5: // Save changes
                    if (saveMissions(missions, missionCount)) {
                        cout << "Database saved successfully!" << endl;
                        dataChanged = false;
                    } else {
                        cout << "Failed to save database. Changes might be lost." << endl;
                    }
                    break;

                case 6: // Quit
                    if (dataChanged) {
                        char saveChoice;
                        cout << "You have unsaved changes. Would you like to save before quitting? (y/n): ";
                        cin >> saveChoice;

                        if (toupper(saveChoice) == 'Y') {
                            if (saveMissions(missions, missionCount)) {
                                cout << "Database saved successfully!" << endl;
                            } else {
                                cout << "Failed to save database. Changes might be lost." << endl;
                            }
                        }
                    }
                    cout << "Thank you for using the Space Mission Database. Goodbye!" << endl;
                    break;
            }
        }
    } while (choice != 6);

    return 0;
}