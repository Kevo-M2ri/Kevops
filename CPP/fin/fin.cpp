/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi.
   Date:        December 8, 2024.
   Assignment:  CS-161A Final Project.
   Description: This prompts the user to enter a goal in miles for their
                weekly exercise and checks for validity of the inputted number.
                It then calculates then asks user to enter the miles exercised
                on each day, then calculates and outputs the total miles
                exercised. It then tells the user if they have reached, exceeded
                or fallen short on their goal.
   Inputs:      goal, and miles as integers.
   Outputs:     totalMiles, and difference from goal as integers.
   -----------------------------------------------------------------------****/

#include <iostream>

using namespace std;

// function prototypes
void Welcome();
void GetInput(int& goal);
int CalcTotal();
void Goodbye();

// main function
int main () {
    int milesOfExercise;
    int totalMiles;

    Welcome(); // welcome message function

    // Goal input
    GetInput(milesOfExercise); // Goal set
    if (milesOfExercise <= 0) {
        cout << "\nNo miles tracked this week!" << endl;
    } // not exercised
    else {
        totalMiles = CalcTotal();

        cout << "\nYou clocked in " << totalMiles << " miles this week!" << endl;
        if (totalMiles > milesOfExercise) {
            cout << "Made of Steel!! You exceeded your goal by " << (totalMiles - milesOfExercise) << " miles." << endl;
        } // exceeding the set goal
        else if (totalMiles == milesOfExercise) {
            cout << "Congratulations! You reached your goal!" << endl;
        } // reached goal
        else {
            cout << "You tried this time. You had a deficit of " << (milesOfExercise - totalMiles) << " miles from your goal." << endl;
        } // not reached the set goal
    }
    Goodbye(); // goodbye message

    return 0;
}
// welcome function
void Welcome() {
    cout << "Hello! Welcome to MILES OF EXERCISE GOAL calculator!!" << endl;
    cout << "You will enter the miles you want to exercise as your GOAL." << endl;
    cout << "Let's get started!" << endl;
}


// input function
void GetInput(int& goal) {
    cout << "\nHow many miles do you want to walk? ";
    cin >> goal;
    cout << endl;
}

// total miles walked calculations function
int CalcTotal() {
    // local variables declaration
    int miles;
    int totalMiles = 0;
    string weekDay;
    int day;
    bool validInput = false;

    // day of exercise loop
    for (day = 0; day < 7; day++) {
        // current day condition
        switch (day) {
            case 0:
                weekDay = "Sunday";
            break;

            case 1:
                weekDay= "Monday";
            break;

            case 2:
                weekDay = "Tuesday";
            break;

            case 3:
                weekDay = "Wednesday";
            break;

            case 4:
                weekDay = "Thursday";
            break;

            case 5:
                weekDay = "Friday";
            break;

            case 6:
                weekDay = "Saturday";
            break;
        }

        // miles exercised that day and validity check
        do {
            cout << "Enter the number of miles walked on " << weekDay << ": ";
            cin >> miles;

            if (miles < 0) {
                cout << "Error!! You cannot walk negative miles! Please try again." << endl;
            }
            else {
                validInput = true;
                totalMiles += miles;
            }
        } while (!validInput);
    }

    return totalMiles;
}

// Goodbye function
void Goodbye() {
    cout << "\nThank you for using our program!" << endl;
    cout << "Enjoy your time, and see you later!" << endl;
}