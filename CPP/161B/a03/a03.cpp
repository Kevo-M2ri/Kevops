/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        January 36, 2025
   Assignment:  CS-161B Assignment a03
   Description: This program stores a list of scores and the corresponding
                letter grades in two parallel arrays
   Inputs:      
   Outputs:     
   -------------------------------------------------------------------------**/
#include <iostream>
#include <limits>
#include <string>
#include <iomanip>
#include <utility>
using namespace std;

// prototypes declaration
void welcome();
void readScores(double scores[], int &count);
void readDouble(string prompt, double &num);
void calcGrade(double scores[], char grade[], int count);
void printList(double scores[], char grade[], int count);
void sort(double scores[], char grade[], int count);
double median(double socres[], int count);
void goodbye();

const int MAXINPUT = 3;
const int MAXCHAR = 5;

int main() {
    double scores[MAXINPUT];
    char grade[MAXCHAR];
    int count;

    welcome();
    readScores(scores, count);
    printList(scores, grade, count);

    return 0;
}

void welcome() {
    cout << "Welcome to the grade calculator." << endl;
}

void readScores(double scores[], int &count) {
    double nums = 0;
    bool readNext = false;
    count = 0;

    do {
        readDouble("Enter your scores here: (-1 to exit): ", nums);

        if (nums == -1) {
            readNext = false; //exit if -1 is entered
        }
        else if (nums >= 0.0 && nums <= 4.0) {
            if (count < MAXINPUT) {
                scores[count] = nums;
                count ++;
                readNext = true;
            }
            else {
                cout << "Cannot exceeed maximum number of scores!" << endl;
                readNext = false; //don't read if array is full
            }
        }
        else {
            cout << "Error!!! Score must be between 0 and 4!. Please try again." << endl;
            readNext = true;
        }
    } while(readNext);
}

void readDouble(string prompt, double &num) {
    bool validDouble = false;

    while (!validDouble) {
        cout << prompt;
        cin >> num;

        if (cin.fail() || num < 0.0){
            cin.clear(); //clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //skip unwanted input
            cout << "Error!! Unrecognized scores!! Please input valid scores!" << endl;
        }
        else {
            validDouble = true; //valid input
        }
    }
}

void calcGrade(double scores[], char grade[], int count) {
    for (int i = 0; i <= count; i++){
        if (scores[i] > 3.3) {
            grade[i] = 'A';
        }
        else if (scores[i] > 2.7 && scores[i] <= 3.3) {
            grade[i] = 'B';
        }
        else if (scores[i] > 1.9 && scores[i] <= 2.7) {
            grade[i] = 'C';
        }
        else if (scores[i] > 1.1 && scores[i] <= 1.9) {
            grade[i] = 'D';
        }
        else{
            grade[i] ='F';
        }
    }
}
void printList(double scores[], char grade[], int count){
    cout << setw(10) << left << "Your score";
    cout << setw(5) << right << "Your Grade" << endl;
    cout << "---------------------------------------" << endl;

    for(int i = 0; i < count; i++) {
        cout << setw(10) << left << scores[i];
        cout << setw(5) << right << grade[i];
    }
}

void sort(double scores[], char grade[], int count) {
    int i;
    int j;
    double min;
    for (i = 0; i < count; i ++) {
        cout << "List: " << scores[i] << endl;
        cout << "Count: " << endl; //Fixme size of array

        min = scores[0];
        for (j = i + 1; j< count; j++) {
            if(scores[j] < min) {
                min = scores[j];
            }
        }
        if (min != scores[i]) {
            swap(min, scores[i]);
        }
    }
}

double median(double socres[], int count);
void goodbye();