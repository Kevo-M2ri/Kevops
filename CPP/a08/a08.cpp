#include <iostream>
#include <limits>
#include <string>
#include <iomanip>

using namespace std;

const double ASSIGNMENT_WEIGHT = 0.6;
const double MIDTERM_WEIGHT = 0.2;
const double FINAL_WEIGHT = 0.2;

// function prototypes
void Welcome();
int ReadInt(string prompt);
double ReadScore(string prompt);
double AssignAverage(int numAssigns);
double CalcFinalScore(double assignAvg, double midterm, double final);
char CalcLetterGrade(double finalScore);

int main () {
    int numAssignments;
    double assignmentAverage;
    double midTermScore;
    double finalsScore;
    double allTermScore;
    char termGrade;

    Welcome();

    numAssignments = ReadInt("Input the number of assignments taken: ");

    assignmentAverage = AssignAverage(numAssignments);

    midTermScore = ReadScore("Enter the midterm exam score: ");
    finalsScore = ReadScore("Enter the final exam score: ");

    allTermScore = CalcFinalScore(assignmentAverage, midTermScore, finalsScore);

    termGrade = CalcLetterGrade(allTermScore);

    cout << fixed << setprecision(1);
    cout << "The score for the whole term is: " << allTermScore << endl;
    cout << "Your grade for the term is: " << termGrade << endl;

    cout << "Thank you for using the calculator >>>> Goodbye!!" << endl;


    return 0;
}

// banner
void Welcome() {
    cout << "Hello!! Welcome to the grade calculator!\n";
    cout << "You will enter the number of assignments taken throughout the term.\n";
    cout << "I will validate the data keyed in and output the final score and grade if data is valid.\n";
    cout << "Let's begin!!" << endl;
}

// readInt
int ReadInt (string prompt) {
    int assignments;
    bool validInput = false;

    do {
        cout << "Input the number of assignments completed: ";
        cin >> assignments;

        if (cin.fail() || assignments < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!! \nInvalid input. Please enter a valid non-negative integer!!\n";
        }
        else {
            validInput = true;
        }
    }
    while(!validInput);

    return assignments;
}

double ReadScore(string prompt) {
    double score;
    bool validInput = false;
    int count = 0;
    int numAssigns = ReadInt("Number of Assignments"); 

    while (count <= numAssigns) {
        cout << "input your score for assignment " << count + 1 << ": " << endl;
        cin >> score;

        if (cin.fail() || score < 0.0 || score > 4.0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not a valid input! Score can only be between 0 and 4.0!!" << endl;
        }
        else {
            validInput = true;
        }
        ++count;
    }

    return score;
}

double AssignAverage (int numAssignments) {
    double average;
    double total = 0.0;
    double score;
    for (int i = 0; i < numAssignments; ++i) {
        score =  ReadScore("Enter the score for the assignment (0-4.0): ");
        total += score;
    }
    average = total / numAssignments;

    return average;
}

double CalcFinalScore(double assignAvg, double midterm, double final) {
    double finalScore;

    finalScore = (assignAvg * ASSIGNMENT_WEIGHT) + (midterm * MIDTERM_WEIGHT) + (final * FINAL_WEIGHT);

    return finalScore;
}

char CalcLetterGrade(double finalScore) {
    if (finalScore >= 3.6) {
        return 'A';
    }
    else if (finalScore >= 3.0) {
        return 'B';
    }
    else if (finalScore >= 2.0) {
        return 'C';
    }
    else if (finalScore >= 1.0) {
        return 'D';
    }
    else {
        return 'F';
    }
}