/*------------------------------------------------------------------
  This project is a simple database for space missions. It allows
  the user to add, remove, search, and display missions. The data is
  stored in a file called "missions.txt". The user can save changes
  to the file before quitting the program. The program uses a struct
  to store mission data and a few functions to interact with the data.
  The program also includes a few helper functions to validate user
  input and clear the input buffer. The program is menu-driven and
  uses a loop to keep running while the user chooses to remove, add,
  search or display missions until the user chooses to quit.
  ------------------------------------------------------------------*/
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
                    
                    cout << "Thank you for using the Space Mission Database. Goodbye!" << endl;
                    break;
            }
        }
    } while (choice != 6);

    return 0;
}