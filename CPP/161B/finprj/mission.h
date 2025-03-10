#ifndef MISSION_H_
#define MISSION_H_

#include <iostream>
#include <fstream>
#include <cstring>
#include <cctype>
#include <iomanip> // Added for setw and setprecision

using namespace std;

struct SpaceMission {
    char name[50];              // Mission name
    char launchSite[100];       // Launch site
    char rocketType[100];       // Rocket type and mission details
    double cost;                // Mission cost
    char status[20];            // Mission status (Success/Failure)
};

// File operations
int loadMissions(SpaceMission missions[], int maxSize);

// Display functions
void displayMenu();
void displayMissions(const SpaceMission missions[], int count);

// Mission management functions
bool addMission(SpaceMission missions[], int& count, int maxSize);
void findMissions(const SpaceMission missions[], int count, const char searchTerm[]);
bool removeMission(SpaceMission missions[], int& count, const char name[]);

// Utility functions
bool isValidChoice(int choice, int min, int max);
void clearInputBuffer();

#endif