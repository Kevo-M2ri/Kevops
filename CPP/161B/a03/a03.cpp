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
double median(double scores[], int count);
void goodbye();

const int MAXINPUT = 20; // constant definition

//function main
int main() {
    //variables declaration
    double scores[MAXINPUT];
    char grade[MAXINPUT];
    int count;

    welcome(); //welcome message call
    readScores(scores, count); //function to read user inputs call
    calcGrade(scores, grade, count); //function to calculate grades call
    printList(scores, grade, count); //function to output scores and calculated grades
    goodbye(); //goodbye message call

    return 0;
}

// function welcome()
void welcome() {
    cout << "Welcome to my parallel arrays program." << endl;
    cout << "Enter your scores here (Enter -1 to exit): " << endl;
    cout << "\n(Scores must be between 0 and 4 inclusive)!!" << endl;
}

// function readScores()
void readScores(double scores[], int &count) {
    // variables declarations
    double num = 0;
    count = 0;
    bool readNext = true;

    while (count < MAXINPUT) {
        readDouble(">>>   ", num);

        if (num == -1) {
            break; //exit if -1 is entered
        }
        else if (num >= 0 && num <= 4) {
            scores[count] = num;
            count ++;
        }// enter values between 0 and 4 inclusive
        else {
            cout << "Error!!! Score must be between 0 and 4! Please try again." << endl;
        } // error message if scores are not within range
    }
} //do not exceed Maximum number of inputs

// readDouble function
void readDouble(string prompt, double &num) {
    bool validDouble = false; //boolean for validity of data inputted check

    while (!validDouble) {
        cout << prompt;
        cin >> num;

        if (cin.fail() || num < -1){
            cin.clear(); //clear the error state
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //skip unwanted input
            cout << "Error!! Unrecognized scores!! Please input valid scores!" << endl; //output error message
        } //condition if input is invalid
        else {
            validDouble = true; //valid input
        } //input is valid
    }
}

//calculate grade function
void calcGrade(double scores[], char grade[], int count) {
    for (int i = 0; i < count; i++){
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
    }//repetitive check for conditions to assign grades to a score ata given position
}

//print of outputs function
void printList(double scores[], char grade[], int count){
    cout << fixed << setprecision(1); //number of decimal places to be output
    cout << "The list of scores and corresponding grades:" << endl;
    cout << setw(10) << left << "Your score" << setw(20) << right << "Your Grade" << endl; //improving readability through spacing 
    cout << setw(10) << left << "-----------" << setw(19) << right << "-----------" << endl;
    for(int i = 0; i < count; i++) {
        cout << setw(10) << left << scores[i] << setw(15) << right << grade[i] << endl; //
    } //looping to output all items in the array

    cout << "\nThe sorted list is: " << endl;
    sort(scores, grade, count); // sort function call
    cout << "The list of scores and corresponding grades:" << endl;
    cout << setw(10) << left << "Your score" << setw(20) << right << "Your Grade" << endl;
    cout << setw(10) << left << "-----------" << setw(19) << right << "-----------" << endl;
    for (int i = 0; i < count; i++) {
        cout << setw(10) << left << scores[i] << setw(15) << right << grade[i] << endl;
    }//loping to output the sorted array

    cout << "\nThe median is: " << median(scores, count) << endl; //median function call and median output
}

//sorting array elements functions
void sort(double scores[], char grade[], int count) {
    for (int i = 0; i < count - 1; i++) {
        int minIndex = i; //initialize minIndex as i
        for (int j = i + 1; j < count; j++) {
            if(scores[j] < scores[minIndex]) {
                minIndex = j;
            } 
        } //minIndex is set to index with minimum array
        if (minIndex != i) {
            swap(scores[i], scores[minIndex]);
            swap(grade[i], grade[minIndex]);
        } //sorting arrays scores[] and grade[]
    } // array is sorted in ascending order
}

//median find function
double median(double scores[], int count) {
    if (count % 2 == 0) {
        return (scores[(count / 2) - 1] + scores[count / 2]) / 2.0;
    } // median if number of items in scores[] is even
    else {
        return scores[count / 2];
    } //median if number of items in scores[] is odd
}

//goodbye function
void goodbye() {
    cout << "\nThank you for using my parallel array program. Goodbye!" << endl;
}