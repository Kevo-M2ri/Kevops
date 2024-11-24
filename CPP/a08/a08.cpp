/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        November 24, 2024
   Assignment:  CS-161A Assignment a08
   Description: This program uses functions to ask the user to input the
                number of assignments, and the scores for each assignment,
                midterm and the finals and validates the input data. It then
                calculates and outputs the final score for the student and
                the grade of the student.
   Inputs:      assignments as an iteger, score as a double
   Outputs:     final score as a double, and final grade as a character
   -----------------------------------------------------------------------****/

#include <iostream>
#include <limits>
#include <string>
#include <iomanip>

using namespace std;

// function prototypes
void Welcome();
int ReadInt(string prompt);
double ReadScore(string prompt);
double AssignAverage(int numAssigns);
double CalcFinalScore(double assignAvg, double midterm, double final);
char CalcLetterGrade(double finalScore);

// constants definitions
const double ASSIGNMENT_WEIGHT = 0.6;
const double MIDTERM_WEIGHT = 0.2;
const double FINAL_WEIGHT = 0.2;

// main function
int main () {

    // variables declarations
    int numAssignments;
    double assignmentAverage;
    double midTermScore;
    double finalsScore;
    double allTermScore;
    char termGrade;

    // banner
    Welcome();

    //function calls
    numAssignments = ReadInt("\nInput the number of assignments completed (0-10): ");
    assignmentAverage = AssignAverage(numAssignments);
    midTermScore = ReadScore("\nEnter the midterm exam score: ");
    finalsScore = ReadScore("Enter the final exam score: ");
    allTermScore = CalcFinalScore(assignmentAverage, midTermScore, finalsScore);
    termGrade = CalcLetterGrade(allTermScore);

    // program outputs
    cout << fixed << setprecision(1);
    cout << "\nThe score for the whole term is: " << allTermScore << endl;
    cout << "Your grade for the term is: " << termGrade << endl;

    cout << "\nThank you for using the calculator >>>> Goodbye!!" << endl;

    return 0;
}

// banner
void Welcome() {
    cout << "Hello!! Welcome to the grade calculator!\n";
    cout << "You will enter the number of assignments taken throughout the term.\n";
    cout << "I will validate the data keyed in and output the final score and grade if data is valid.\n";
    cout << "Let's begin!!" << endl;
}

// read number of assignments function
int ReadInt (string prompt) {
    int assignments;
    bool validInput = false;

    do {
        cout << prompt; // user prompt for number of assignments
        cin >> assignments;

        if (cin.fail() || assignments < 0 || assignments > 10) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!! Invalid input. Please enter a number between 0 and 10\n";
        }
        else {
            validInput = true;
        }
    }
    while(!validInput); // validity of data inputted condition

    return assignments;
}

// read scores function
double ReadScore(string prompt) {
    double score;
    bool validInput = false;

    do {
        cout << prompt << endl; //user prompt for scores per assignment
        cin >> score;

        if (cin.fail() || score < 0.0 || score > 4.0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not a valid input! Score can only be between 0 and 4.0!!" << endl;
        }
        else {
            validInput = true;
        }
    }
    while (!validInput); // validity of data inputted condition

    return score;
}

// average calcuclation funtion
double AssignAverage (int numAssignments) {
    double average;
    double total = 0.0;
    double score;
    int i;
    string prompt;

    if (numAssignments == 0) {
        return 0.0; //no assignments done
    }
    for (i = 1; i <= numAssignments; ++i) {
        prompt = "Enter score for assignment " + to_string(i) + ": ";
        total += ReadScore(prompt); //inputted scores function call
    }
    average = total / numAssignments;

    return average;
}

// final score calculation function
double CalcFinalScore(double assignAvg, double midterm, double final) {
    double finalScore;

    finalScore = (assignAvg * ASSIGNMENT_WEIGHT) + (midterm * MIDTERM_WEIGHT) + (final * FINAL_WEIGHT);

    return finalScore;
}


// grade assigning function
char CalcLetterGrade(double finalScore) {
    if (finalScore >= 3.3) {
        return 'A';
    }
    else if (finalScore >= 2.8) {
        return 'B';
    }
    else if (finalScore >= 2.0) {
        return 'C';
    }
    else if (finalScore >= 1.2) {
        return 'D';
    }
    else {
        return 'F';
    }
}