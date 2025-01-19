// NOTE: This template is to be used for discussion ONLY! You must
// use the required Algorithmic Design Document for all Assignments.
/******************************************************************************
# Author:           Kelvin Muturi and Kate Stingle
# Lab:              Discussion #2
# Date:             January 18, 2025
# Description:      This program prompts the user to enter letters, numbers and 
                    characters for a password. It uses input data validation and 
                    repromts until the inputted information is valid. The program 
                    then constructs the password and outputs it back to the user.
# Input:            char[] name, number
                    char symbol
# Output:           string password
# Sources:          Discussion 2 assignment specifications
#******************************************************************************/

#include <iostream>
#include <cstring>
#include <cctype>
#include <limits>
using namespace std;

// function headers
void welcome();
void getInput(char name[], char number[], char &symbol);
void passcode(char password[]);
void goodbye();
bool isCharArrayAlpha(char cstring[]);
bool isCharArrayDig(char cstring[]);

//constants
const int MAXCHAR = 20;
const int MAXNUMS = 5;
//fucntion main
int main () {
    char password[27];

    welcome();
    passcode(password);
    goodbye();

    return 0;
}

void welcome() { //prints welcome 
    cout << "Hello! Follow prompts to create your password!" << endl;
}

void getInput(char name[], char number[], char &symbol) {
    cout << "Input a name you can easily remember: ";
    cin.clear();
    cin.getline(name, MAXCHAR);

    while (!isCharArrayAlpha(name)) {
        cout << "Error!! Not a name! Try again." << endl;
        cin.getline(name, MAXCHAR);
    } // name is valid

    cout << "Enter a four digit number: ";
    cin.clear();
    cin.getline(number, MAXNUMS);

    while (!isCharArrayDig(number)) {
        cout << "Error!! Expected numbers! Please try again later." << endl;
        cin.getline(number, MAXNUMS);
    } // numbers are valid
    
    cout << "Enter a symbol on your keyboard: ";
    cin >> symbol;
    while (cin.fail() || !ispunct(symbol)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Error!! Not a symbol. Try again" << endl;
        cin >> symbol; //symbol is valid
    }    
}

// calls getInput to prompt user for password
// generates and outputs password
void passcode(char password[]) {
    char name[MAXCHAR];
    char number[MAXNUMS];
    char symbol;
    getInput(name, number, symbol);
    strcpy(password, name); // appends name
    strncat(password, number, 5); // appends numbers
    password[strlen(password)] = symbol; //appends symbol
    password[strlen(password)] = '\0'; //null character = \0
    cout << password;
}
//checks validity for alpha for a char array
bool isCharArrayAlpha(char cstring[]){
    for(int i = 0; i < strlen(cstring) ; i++){
        if(!isalpha(cstring[i])){
            return false;
        }
    }
    return true;
}

//validity check for numbers for char array
bool isCharArrayDig(char cstring[]){
    for(int i = 0; i < strlen(cstring) ; i++){
        if(!isdigit(cstring[i])){
            return false;
        }
    }
    return true;
}