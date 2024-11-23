#include <iostream>
#include <limits>

using namespace std;

// function prototypes
void Welcome();
int ReadInt(string prompt);
double ReadScore(string prompt);
double AssignAverage(int numAssigns);
double CalcFinalScore(double assignAvg, double midterm, double final);
char CalcLetterGrade(double finalScore);

int main () {
    int numAssignments;
    double assignmentScore;
    Welcome();

    numAssignments = ReadInt("Input an integer: ");

    return 0;
}

// banner
void Welcome() {
    cout << "Hello!! Welcome to the grade calculator!" << endl;

}

// readInt
int ReadInt (string prompt) {
    int assignments;
    bool validInput = false;

    do {
        cout << "Input the number of assignments completed: ";
        cin >> assignments;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Fixme conditions
            cout << "Error!! \nInvalid input. Please enter a valid integer!!\n";
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

    do {
        cout << "input your score for the assignments: ";
        cin >> score;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // fixme conditions
            cout << "Not a valid input! Try again later\n";
        }
        else if ((score < 0.0) || (score > 4.0)) {
            cout << "Score must be between 0 and 4.0. Try again later\n";
        }
        else {
            validInput = true;
        }
    }
    while(!validInput);

    return score;
}

double AssignAverage (int numAssignments) {
    double average;

    return average;
}