#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <limits>
using namespace std;

void welcome();
void displayMenu();
void readOption(char &option);
void encode(char encodeFileName[]);
void readInput(char fName[], char lName[], bool &lateFlag);
void readInput(char parseID[], char fileName[]);
void readTime(char strTime[]);
void funcToLower(char myName[]);
void goodbye();

const int MAXCHAR = 20;

int main() {
    char choice;
    char encodedName[MAXCHAR * 5];

    welcome();

    do {
        displayMenu();
        readOption(choice);

        if (tolower(choice) == 'e') {
            encode(encodedName);
            cout << "Encoded file name: " << encodedName << endl;
        }
    
    } while (tolower(choice != 'q'));

    goodbye();

    return 0;
}

void welcome() {
    cout << "Welcome to the encoder..." << endl;
}

void displayMenu() {
    cout << "You can choose to encode or quit." << endl;
    cout << "(E)ncode a file name" << endl;
    cout << "(Q)uit" << endl;
    cout << "Choose one of the choices to continue: " << endl;
}
void readOption(char &option) {
    bool validEntry = false;

    while (!validEntry) {
        cout << ">>> ";
        cin >> option;
        if (tolower(option) != 'e' && tolower(option) != 'q' ) {
            cout << "Error!! Entry not recognized! Please try again" << endl;
        } //check for other values
        else {
            validEntry = true;
        }
    }
}
void encode(char encodeFileName[]){
    char fName[MAXCHAR];
    char lName[MAXCHAR];
    bool lateFlag;
    char parseID[5];
    char fileName[MAXCHAR];
    char strTime[MAXCHAR];

    readInput(fName, lName, lateFlag);
    readInput(parseID, fileName);
    readTime(strTime);

    strcpy(encodeFileName, lName);
    strcat(encodeFileName, "_");
    strcat(encodeFileName, fName);
    strcat(encodeFileName, "_");

    if (lateFlag) {
        strcat(encodeFileName, "LATE_");
    }

    strcat(encodeFileName, parseID);
    strcat(encodeFileName, "_");
    strcat(encodeFileName, strTime);
    strcat(encodeFileName, "_");
    strcat(encodeFileName, fileName);  
}

void readInput(char fName[], char lName[], bool &lateFlag) {
    char response;

    cout << "What is your first name? " << endl;
    cin >> fName;
    funcToLower(fName);

    cout << "What is your last name? " << endl;
    cin >> lName;
    funcToLower(lName);

    cout << "Was your assignement late (y/n)? ";
    cin >> response;
    while (tolower(response) != 'y' && tolower(response) != 'n') {
        cout << "Invalid input. Please enter 'y' or 'n': ";
        cin >> response;
    }
    lateFlag = (tolower(response) == 'y');
}

void readInput(char parseID[], char fileName[]) {
    char stdID[MAXCHAR];
    cout << "Enter your student ID (xxx-xx-xxxx): ";
    cin >> stdID;

    while (strlen(stdID) != 11 || stdID[3] != '-' || stdID[6] != '-') {
        cout << "Invalid format! Enter student ID in the format xxx-xx-xxxx: ";
        cin >> stdID;
    }

    strncpy(parseID, stdID +7, 4);
    parseID[4] = '\0';
    cout << "Input file name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(fileName, MAXCHAR);
}

void readTime(char strTime[]) {
    int hrs = 0;
    char colon;
    int mins = 0;

    cout << "Enter time in the HH:MM format: ";
    cin >> hrs >> colon >> mins;
     while (colon != ':' || hrs < 0 || hrs > 23 || mins < 0 || mins > 59) {
        cout << "Invalid time format. Please enter time in HH:MM format: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> hrs >> colon >> mins;
    }

    snprintf(strTime, MAXCHAR, "%02d%02d", hrs, mins); // Format time as HHMM

    strncpy(strTime, to_string(hrs).c_str(), 10); // convert hours into string then c_string and assign to strTime
    strTime[strlen(strTime)] = colon; //add colon into string
    strcat(strTime, to_string(mins).c_str()); // convert mminutes into string then c_string and assign to strTime
}

void funcToLower(char myName[]) {
    for (int i = 0; myName[i] != '\0'; i++) {
        myName[i] = tolower(myName[i]);
    }
}

void goodbye() {
    cout << "Password Created successfully. Goodbye!" << endl;
}
