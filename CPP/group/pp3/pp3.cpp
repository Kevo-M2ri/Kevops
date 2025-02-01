// NOTE: This template is to be used for discussion ONLY! You must
// use the required Algorithmic Design Document for all Assignments.
/******************************************************************************
# Author:           Kate Stingle, Kelvin Muturi, Dammon Bowen
# Lab:              Discussion #4
# Date:             January 31st, 2025
# Description:      This program reads a list of integers from input into an array and modifies the array by shifting numbers to the right and moving the numbers to the front of the list.
# Input:            - Int readInt() has int num (num will be returned from readInt(), used for numItems and shiftIndex)
                    - Int arr[]  for array[]
# Output:           - int arr[] (read to and modified to be outputted)
# Sources:          Discussion 4 Specifications
#******************************************************************************/

#include <iostream>
#include <string>
using namespace std;

// FUNCTION HEADERS
int readInt(string prompt); // reads integer given prompt for numItems and shiftIndex, uses data validation
void endToFront (int arr[], int length); // moves the last element of the array to the front and shifts rest of items to the right
void printArray(int arr[], int items); // prints the array
void readArray(int arr[], int numItems); // reads to each item of the array numItems times


// CONSTANTS
string const ERR_MSG = "Invalid Input!! Must input a valid positive integer!!";
int const MAX_CHAR = 50;  // max elementsin

// MAIN
int main() {
    int numItems; // number of items in array
    int arr[MAX_CHAR]; // define the 1 array to be read to, modified and printed out
    int shiftIndex; // the index to start shifting from 
    numItems = readInt("Number of items: "); // read to num items in array
    readArray(arr, numItems); // read to the array
    shiftIndex = readInt("Shift index: "); // read to the shift index
    for(int n = 0 ; n < (numItems-shiftIndex) ; n++){
        endToFront(arr, numItems); // moves the last index item to ffront of the list
    } // does this (numItems-shiftIndex) times
    // now the array is shifted correctly
    printArray(arr, numItems); // print array    
    return 0;
}


// FUNCTION DEFINITIONS
// reads integer given prompt for numItems and shiftIndex, uses data validation
int readInt(string prompt) {
    cout << prompt;
    int num;
    cin >> num;
    while (cin.fail() || num <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cin.clear();
        cout << ERR_MSG << endl;
        cout << prompt;
        cin >> num;
    }
    return num;
}

// reads to each item of the array numItems times}
void readArray(int arr[], int numItems) {
    cout << "Input Array: ";
    for (int i = 0; i < numItems; i++) {
        cin >> arr[i];
    } 
}

// moves the last element of the array to the front and shifts rest of items to the right}
void endToFront(int arr[], int length) {
    int temp = arr[length -1];
    for (int i = length - 1; i > 0; i--) {
        arr[i] = arr[i - 1];
    }
    arr[0] = temp;
}
//prints the array
void printArray(int arr[], int items) {
    cout << "modified array: ";
    for (int i = 0; i < items; i++) {
        cout << arr[i] << " ";
    }
}