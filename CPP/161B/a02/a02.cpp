/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        January 19, 2025
   Assignment:  CS-161B Assignment a02
   Description: This program gives the user a menu with choices, allowing them
                to pick a choice, then asks them some questions, giving them
                results whilst checking the validity of their responses. It
                then outputs an encoded file name made from both names, whether
                assignment was submitted late, student ID, file name and time
                of submission.
   Inputs:      option, response, and colon as characters, fName, lName, stdID,
                parseID, and fileName as character arrays, lateFlag as a 
                boolean, hrs and mins as integers.
   Outputs:     encoded file name as a character array.
   -------------------------------------------------------------------------**/
#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>
#include <limits>
using namespace std;

// function prototypes
void welcome();
void displayMenu();
void readOption(char &option);
void encode(char encodeFileName[]);
void readInput(char fName[], char lName[], bool &lateFlag);
void readInput(char parseID[], char fileName[]);
void readTime(char strTime[]);
void funcToLower(char myName[]);
void goodbye();

//constants declaration
const int MAXCHAR = 20;

// main function
int main() {
    char choice;
    char encodedName[MAXCHAR * 5];

    welcome();

    do {
        displayMenu();
        readOption(choice);

        if (tolower(choice) == 'e') {
            encode(encodedName);
            cout << "\nEncoded file name: " << encodedName << endl;
        }
    
    } while (tolower(choice != 'q')); //quit clause

    goodbye();

    return 0;
}

// welcome message
void welcome() {
    cout << "Welcome to the encoder..." << endl;
}

//menu options
void displayMenu() {
    cout << "\nYou can only choose to encode or quit." << endl;
    cout << "(E)ncode a file name" << endl;
    cout << "(Q)uit" << endl;
    cout << "Choose one of the choices to continue: " << endl;
}

//option input and validation
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

// encoding function
void encode(char encodeFileName[]){
    //variables declaration
    char fName[MAXCHAR];
    char lName[MAXCHAR];
    bool lateFlag;
    char parseID[5];
    char fileName[MAXCHAR];
    char strTime[MAXCHAR];

    
    readInput(fName, lName, lateFlag); //names and late function call
    readInput(parseID, fileName); // id and filename input fucntion call
    readTime(strTime); //reading time of submision

    //copying names into encodeFileName
    strcpy(encodeFileName, fName);
    strcat(encodeFileName, "_");
    strcat(encodeFileName, lName);
    strcat(encodeFileName, "_");

    //late condition
    if (lateFlag) {
        strcat(encodeFileName, "LATE_");
    }

    // student ID and file name copying into encodeFileName
    strcat(encodeFileName, parseID);
    strcat(encodeFileName, "_");
    strcat(encodeFileName, strTime);
    strcat(encodeFileName, "_");
    strcat(encodeFileName, fileName);  
}

// function to read user names and lateness in submission
void readInput(char fName[], char lName[], bool &lateFlag) {
    char response; // variable declaration

    cout << "\nWhat is your first name? " << endl;
    cin >> fName;
    funcToLower(fName); // convertion to lowercase

    cout << "What is your last name? " << endl;
    cin >> lName;
    funcToLower(lName); //to lowercase

    cout << "Was your assignment late (y/n)? ";
    cin >> response;
    while (tolower(response) != 'y' && tolower(response) != 'n') { //input validity condition
        cout << "Invalid input. Please enter 'y' or 'n': ";
        cin >> response;
    }
    lateFlag = (tolower(response) == 'y');
}

// student id and filename reading function
void readInput(char parseID[], char fileName[]) {
    char stdID[MAXCHAR];
    cout << "Enter your student ID (xxx-xx-xxxx): ";
    cin >> stdID;

    while (strlen(stdID) != 11 || stdID[3] != '-' || stdID[6] != '-') {
        cout << "Invalid format! Enter student ID in the format xxx-xx-xxxx: ";
        cin >> stdID;
    } //id format check

    strncpy(parseID, stdID + 7, 4); //copy the last 4 characters of stdID to parseID
    parseID[4] = '\0';
    cout << "Input file name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.getline(fileName, MAXCHAR);
}

// time reading function
void readTime(char strTime[]) {
    //variable declaration
    int hrs = 0;
    char colon;
    int mins = 0;

    cout << "Enter the time of submission(military time i.e. 13:00 for 1:00pm): ";
    cin >> hrs >> colon >> mins;
     while (colon != ':' || hrs < 0 || hrs > 23 || mins < 0 || mins > 59) {
        cout << "Invalid time format. Please enter time in HH:MM format: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin >> hrs >> colon >> mins;
    } //time format check

    snprintf(strTime, MAXCHAR, "%02d%02d", hrs, mins); // Format time as HHMM

    strncpy(strTime, to_string(hrs).c_str(), 10); // convert hours into string then c_string and assign to strTime
    strTime[strlen(strTime)] = colon; //add colon into string
    strcat(strTime, to_string(mins).c_str()); // convert mminutes into string then c_string and assign to strTime
}

//convert to lowercase function
void funcToLower(char myName[]) {
    for (int i = 0; myName[i] != '\0'; i++) {
        myName[i] = tolower(myName[i]);
    }
}

// goodbye function
void goodbye() {
    cout << "\nPassword Created successfully. Goodbye!" << endl;
}