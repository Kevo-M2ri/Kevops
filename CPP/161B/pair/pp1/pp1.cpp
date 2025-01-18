
#include <iostream>
#include <cstring>
#include <cctype>
#include <limits>
using namespace std;

void welcome();
void getInput(char name[], char number[], char &symbol);
void passcode(char password[]);
void goodbye();
bool isCharArrayAlpha(char cstring[]);
bool isCharArrayDig(char cstring[]);

const int MAXCHAR = 20;
const int MAXNUMS = 5;

int main () {
    char password[27];

    welcome();
    passcode(password);

    return 0;
}

void welcome() {
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

void passcode(char password[]) {
    char name[MAXCHAR];
    char number[MAXNUMS];
    char symbol;

    getInput(name, number, symbol);
    strcpy(password, name);
    strncat(password, number, 5);
    password[strlen(password)] = symbol;
    password[strlen(password)] = '\0'; //null character = \0 not \n??
    cout << password;
}

bool isCharArrayAlpha(char cstring[]){
    for(int i = 0; i < strlen(cstring) ; i++){
        if(!isalpha(cstring[i])){
            return false;
        }
    }
    return true;
}

bool isCharArrayDig(char cstring[]){
    for(int i = 0; i < strlen(cstring) ; i++){
        if(!isdigit(cstring[i])){
            return false;
        }
    }
    return true;
}