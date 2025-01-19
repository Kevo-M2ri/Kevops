#include <iostream>
#include <cstring>
#include <cctype>
#include <iomanip>
using namespace std;

void welcome();
void displayMenu();
void readOption(char &option);
void encode(char encodeFileName);
void readInput(char fName[], char lName[], bool &lateFlag);
void readInput(char parseID[], char fileName[]);
void readTime(char strTime[]);
void toLower();
void goodbye();

const int MAXCHAR = 15;

int main() {
    char choice;
    welcome();

    displayMenu();
    readOption(choice);

    return 0;
}

void welcome() {
    cout << "Welcome to the encoder..." << endl;
}

void displayMenu() {
    cout << "You can choose to encode or quit." << endl;
    cout << "Choose one of the choices to continue: " << endl;
    cout << "(E)ncode a file name" << endl;
    cout << "(Q)uit" << endl;
}
void readOption(char &option) {
    bool validEntry = false;

    while (!validEntry) {
        cout << ">>> ";
        cin >> option;
        if (option != 'e' && option != 'q' && option != 'E' && option != 'Q') {
            cout << "Error!! Entry not recognized! Please try again" << endl;
        } //check for other values
        else {
            validEntry = true;
        }
    }
}
void encode(char encodeFile){
    char fName[MAXCHAR];
    char lName[MAXCHAR];
    bool lateFlag;
    char parseID[MAXCHAR];
    char fileName[MAXCHAR];
    char strTime[MAXCHAR];
    char name[MAXCHAR];
    char spacer = '_';

    readInput(fName, lName, lateFlag);
    readInput(parseID, fileName);
    readTime(strTime);

    strcpy(name, fName);
    strcat(name, lName);
}
void readInput(char fName[], char lName[], bool &lateFlag) {
    cout << "What is your first name? " << endl;
    cin >> fName;
    toLower(fName);
    cout << "What is your last name? " << endl;
    cin >> lName;
    toLower(lName);

}
void readInput(char parseID[], char fileName[]) {

}

void readTime(char strTime[]) {

}
void toLower(char myName[]) {
    int i;
    for (i = 0; myName[i] != '\0'; i++) {
        myName[i] = tolower(myName[i]);
    }
}