/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        December 3, 2024
   Assignment:  CS-161A Assignment a09
   Description: This program uses functions to ask the user to input the
                number of assignments, and the scores for each assignment,
                midterm and the finals and validates the input data. It then
                calculates and outputs the final score for the student and
                the grade of the student.
   Inputs:      assignments as an integer, score as a double
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
void ReadScore(string prompt, double& num);
double AssignAverage(int numAssigns);
void GetInput(double& midtermScore, double& finalExamScore);
double CalcFinalScore(double assignAvg, double midtermScore, double final);
void CalcLetterGrade(double finalScore, char& letter);

// constants definitions
const double ASSIGNMENT_WEIGHT = 0.6;
const double MIDTERM_WEIGHT = 0.2;
const double FINAL_WEIGHT = 0.2;

// main function
int main () {

    // variables declarations
    int numAssignments;
    double assignmentAverage;
    double midtermScore;
    double finalsScore;
    double allTermScore;
    char termGrade;

    // banner
    Welcome();

    //function calls
    numAssignments = ReadInt("\nInput the number of assignments completed (0-10): ");
    assignmentAverage = AssignAverage(numAssignments);
    GetInput(midtermScore, finalsScore);
    allTermScore = CalcFinalScore(assignmentAverage, midtermScore, finalsScore);
    CalcLetterGrade(allTermScore, termGrade);

    // program outputs
    cout << fixed << setprecision(1);
    cout << "\nThe score for the whole term is: " << allTermScore << endl;
    cout << "Your grade for the term is: ";
    CalcLetterGrade(allTermScore, termGrade);

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
void ReadScore(string prompt, double& score) {
    bool validInput = false;

    do {
        cout << prompt; //user prompt for scores per assignment
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
        ReadScore(prompt, score); //inputted scores function call
        total += score;
    }
    average = total / numAssignments;

    return average;
}

// reading midterm and final exam scores function
void GetInput(double& midtermScore, double& finalExamScore) {
    ReadScore("\nEnter the midterm exam score: ", midtermScore);
    ReadScore("Enter the final exam score: ", finalExamScore);
}

// final score calculation function
double CalcFinalScore(double assignAvg, double midterm, double final) {
    double finalScore;

    finalScore = (assignAvg * ASSIGNMENT_WEIGHT) + (midterm * MIDTERM_WEIGHT) + (final * FINAL_WEIGHT);

    return finalScore;
}


// grade assigning function
void CalcLetterGrade(double finalScore, char& letter) {
    if (finalScore >= 3.3) {
        cout << 'A' << endl;
    }
    else if (finalScore >= 2.8) {
        cout << 'B' << endl;
    }
    else if (finalScore >= 2.0) {
        cout << 'C' << endl;
    }
    else if (finalScore >= 1.2) {
        cout << 'D' << endl;
    }
    else {
        cout << 'F' << endl;
    }
}