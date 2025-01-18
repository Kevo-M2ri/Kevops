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

int main() {
    welcome();

    displayMenu();

    return 0;
}

void welcome() {
    cout << "Welcome to the encoder..." << endl;
}

void displayMenu() {
    cout << "You can choose to encode or quit." << endl;
    cout << "Choose one fo the choices to continue: " << endl;
    cout << "(E)ncode a file name" << endl;
    cout << "(Q)uit" << endl;
}
void readOption(char &option) {

}
void encode(char encodeFile) {

}
void readInput(char fName[], char lName[], bool &lateFlag) {
    cout << "What is your first name? " << endl;
    cin >> fName;
    cout << "What is your last name? " << endl;
    cin >> lName;
}
void readInput(char parseID[], char fileName[]) {

}

void readTime(char strTime[]) {

}
void toLower() {

}