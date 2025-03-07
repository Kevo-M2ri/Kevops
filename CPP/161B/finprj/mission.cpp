#include "mission.h"
#include <iomanip> // Added for setw and setprecision

const char FILENAME[] = "minimission.txt";

int loadMissions(SpaceMission missions[], int maxSize) {
    ifstream inFile(FILENAME);
    int count = 0;

    if (!inFile) {
        cout << "Warning: Could not open file for reading. Starting with empty database." << endl;
        return 0;
    }

    // Skip the header line
    char header[500];
    inFile.getline(header, 500);

    while (count < maxSize && !inFile.eof()) {
        // Read mission name
        inFile.getline(missions[count].name, 50, ';');

        // Stop reading if we've reached the end of file after last mission
        if (inFile.eof()) break;

        // Read launch site
        inFile.getline(missions[count].launchSite, 100, ';');

        // Read rocket type
        inFile.getline(missions[count].rocketType, 100, ';');

        // Read cost
        inFile >> missions[count].cost;
        inFile.ignore(); // Skip the semicolon after cost

        // Read status
        inFile.getline(missions[count].status, 20);

        // Check if the mission was read successfully
        if (inFile.good() || inFile.eof()) {
            count++;
        } else if (!inFile.eof()) {
            // Handle read errors (e.g., invalid data format)
            cout << "Error: Invalid data format in file. Skipping line." << endl;
            inFile.clear(); // Clear the error flag
            inFile.ignore(1000, '\n'); // Skip to the next line
        }
    }

    inFile.close();
    return count;
}

bool saveMissions(const SpaceMission missions[], int count) {
    ofstream outFile(FILENAME);

    if (!outFile) {
        return false;
    }

    // Write header line
    outFile << "Organisation;Location;Detail;Price;Mission_Status" << endl;

    for (int i = 0; i < count; i++) {
        outFile << missions[i].name << ";"
                << missions[i].launchSite << ";"
                << missions[i].rocketType << ";"
                << missions[i].cost << ";"
                << missions[i].status;

        if (i < count - 1) {
            outFile << endl;
        }
    }

    outFile.close();
    return true;
}

void displayMenu() {
    cout << endl;
    cout << "--------- SPACE MISSION DATABASE ---------" << endl;
    cout << "1. Display all missions" << endl;
    cout << "2. Add a new mission" << endl;
    cout << "3. Find a mission" << endl;
    cout << "4. Remove a mission" << endl;
    cout << "5. Save changes" << endl;
    cout << "6. Quit" << endl;
}

void displayMissions(const SpaceMission missions[], int count) {
    if (count == 0) {
        cout << "No missions in the database." << endl;
        return;
    }

    cout << endl;
    cout << "MISSION DATABASE:" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << left << setw(15) << "Name" 
         << left << setw(35) << "Launch Site" 
         << left << setw(20) << "Rocket Type"
         << left << setw(8) << "Cost" 
         << "    " << left << "Status" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++) {
        cout << left << setw(15) << missions[i].name
             << left << setw(35) << missions[i].launchSite
             << left << setw(20) << missions[i].rocketType
             << left << setw(8) << fixed << setprecision(2) << missions[i].cost
             << "    " << left << missions[i].status << endl;
    }

    cout << endl;
}

bool addMission(SpaceMission missions[], int& count, int maxSize) {
    if (count >= maxSize) {
        cout << "Error: Database is full. Cannot add more missions." << endl;
        return false;
    }

    SpaceMission newMission;

    // Clear input buffer
    clearInputBuffer();

    cout << "Enter mission name: ";
    cin.getline(newMission.name, 50);

    cout << "Enter launch site: ";
    cin.getline(newMission.launchSite, 100);

    cout << "Enter rocket type: ";
    cin.getline(newMission.rocketType, 100);

    cout << "Enter mission cost: ";
    cin >> newMission.cost;
    cin.ignore(); // Clear the newline character

    cout << "Enter mission status (Success/Failure): ";
    cin.getline(newMission.status, 20);

    missions[count] = newMission;
    count++;

    cout << "Mission added successfully!" << endl;
    return true;
}

void findMissions(const SpaceMission missions[], int count, const char searchTerm[]) {
    bool found = false;

    cout << "Missions matching \"" << searchTerm << "\":" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;
    cout << left << setw(15) << "Name" 
         << left << setw(35) << "Launch Site" 
         << left << setw(20) << "Rocket Type"
         << left << setw(8) << "Cost" 
         << "    " << left << "Status" << endl;
    cout << "-----------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < count; i++) {
        if (strstr(missions[i].name, searchTerm) ||
            strstr(missions[i].launchSite, searchTerm) ||
            strstr(missions[i].rocketType, searchTerm) ||
            strstr(missions[i].status, searchTerm)) {
            cout << left << setw(15) << missions[i].name
                 << left << setw(35) << missions[i].launchSite
                 << left << setw(20) << missions[i].rocketType
                 << left << setw(8) << fixed << setprecision(2) << missions[i].cost
                 << "    " << left << missions[i].status << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "No missions found matching \"" << searchTerm << "\"." << endl;
    }
}

bool removeMission(SpaceMission missions[], int& count, const char name[]) {
    for (int i = 0; i < count; i++) {
        if (strcmp(missions[i].name, name) == 0) {
            // Shift all subsequent missions up
            for (int j = i; j < count - 1; j++) {
                missions[j] = missions[j + 1];
            }
            count--;
            cout << "Mission \"" << name << "\" removed successfully!" << endl;
            return true;
        }
    }

    cout << "Error: Mission \"" << name << "\" not found." << endl;
    return false;
}

bool isValidChoice(int choice, int min, int max) {
    return (choice >= min && choice <= max);
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(1000, '\n');
}