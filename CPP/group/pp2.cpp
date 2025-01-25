// NOTE: This template is to be used for discussion ONLY! You must
// use the required Algorithmic Design Document for all Assignments.
/******************************************************************************
# Author:         Kate Stingle, Dammon , Kelvin
# Lab:              Discussion #2
# Date:             January 26, 2025
# Description:      This program prompts for an age and calculates birth year
# Input:            string name, integer age
# Output:           integer birth year
# Sources:          None
#******************************************************************************/

#include <iostream>
using namespace std;

// FUNCTION HEADERS
bool isSorted(int myArray[], int start, int end);

// CONSTANTS
int MAX_VAL = 20;

// MAIN
int main() {
    //Declare Variables
    int myArray[MAX_VAL];
    int numInts, startIndex, endIndex;
    
    //Prompt for input
    cout << "Number of integers: ";
    cin >> numInts;
    cout << "Enter the values: " << endl;
    //Loop to collect values in index
    for (int i = 0 ; i < numInts ; i++){
        cin >> myArray[i];
    }
    // Prompt for index points
    cout << "Enter the start and end index: ";
    cin >> startIndex >> endIndex;
    // Display results
    if(isSorted(myArray, startIndex, endIndex)){
        cout << "yes, the array is sorted" << endl;
    } else {
        cout << "no, the array is not sorted" << endl;
    }
    cout << "Thank you for using our program!";
    return 0;
}

// fucntion to check if array is sorted
bool isSorted(int myArray[], int startIndex, int endIndex) {
    for (int i = startIndex + 1; i < endIndex; i++){
        if (myArray[i] < myArray[i-1]) {
            return false; //array not sorted
        }
    }
    return true; // array is sorted
}