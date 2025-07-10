#include <iostream>
#include <limits>

using namespace std;

//function prototypes
void welcome();
void validateInput(int);
void checkEvenOdd(int);

//main function
int main() {
    int userInput = 0;

    welcome(); //call welcome function
    
    cout << "Please enter an integer: ";
    cin >> userInput;

    validateInput(userInput); //call validateInput function
    checkEvenOdd(userInput); //call checkEvenOdd function

    cout << "Thank you for using this dummy functions project. Goodbye!" << endl;

    return 0;
}

void welcome() {
    cout <<"Welcome to this dummy functions project!" << endl;
    cout << "You will be prompted to enter an integer." << endl;
    cout << "The program will then do some few stuff with it." << endl;
    cout << "Enjoy!" << endl;
}

void validateInput(int userInput) {
    while (userInput < 0 || cin.fail()) {
        cout << "Invalid input. Please enter a non-negative integer: ";
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        cin >> userInput;
    }
}

void checkEvenOdd(int number) {
    if (number % 2 == 0) {
        cout << "The number " << number << " is even." << endl;
    } else {
        cout << "The number " << number << " is odd." << endl;
    }
}