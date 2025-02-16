/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        February 16, 2025
   Assignment:  CS-161B Assignment a05
   Description: This program reads data from a file and stores it in a 2D array.
                It then displays the data in the array and calculates the average
                of the NCSI data. It also displays the country with the highest
                and lowest GCI.
   Inputs:      country as a 2D character array, gciNcsiData as a 2D integer array,
                size as an integer.
   Outputs:     country and gciNcsiData as 2D arrays, size as an integer.
   -------------------------------------------------------------------------**/

#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <iomanip>
using namespace std;

// constants definition
const int MAX_CHAR = 150;
const int MAX_SIZE = 30;

// function prototypes
void welcome();
bool openFile(ifstream &inFile);
int readData(ifstream &inFile, char country[][MAX_CHAR], double gciNcsiData[][2]);
void displayData(char country[][MAX_CHAR], double gciNcsiData[][2], int size);
void doAnalysis(char country[][MAX_CHAR], double gciNcsiData[][2], int size);
double calcAverage(double gciNcsiData[][2], int count, int column);
void goodbye();

// main function
int main() {
    ifstream inFile; // input file stream
    int size = 0;
    char country[MAX_SIZE][MAX_CHAR]; // 2D array to store country names
    double gciNcsiData[MAX_SIZE][2] = {0}; // 0: GCI, 1: NCSI
    double average = 0.0;

    welcome(); // display welcome message
    cout << endl;

    if (!openFile(inFile)) {
        cout << "Error! File did not open! Program closing!!" << endl;
        exit(0);
    }
    
    size = readData(inFile, country, gciNcsiData);
    displayData(country, gciNcsiData, size);
    cout << endl;

    doAnalysis(country, gciNcsiData, size);
    average = calcAverage(gciNcsiData, size, 0);

    cout << "Average GCI: " << average << endl << endl;

    goodbye(); // display goodbye message

    return 0;
}
// function to display welcome message
void welcome() {
    cout << "Welcome to the GCI and NCSI data analysis program!" << endl;
    cout << "This program reads data from a file and displays it." << endl;
    cout << "It also calculates the average of the NCSI data." << endl;
    cout << "Enjoy!" << endl;
}

// open the file
bool openFile(ifstream &inFile) {
    inFile.open("data2.txt"); // open the file
    if (!inFile.is_open()) {
        return false; // return false if the file is not opened
    }
    return true; // return true if the file is opened
}

// read the data from the file
int readData(ifstream &inFile, char country[][MAX_CHAR], double gciNcsiData[][2]) {
    int size = 0;

    while (size < MAX_SIZE && inFile.getline(country[size], MAX_CHAR, ';')) {
        inFile >> gciNcsiData[size][0]; // read the GCI data
        inFile.ignore(5, ';'); // ignore the semicolon
        inFile >> gciNcsiData[size][1]; // read the NCSI data
        inFile.ignore(100, '\n'); // ignore the newline character
        size++;
    }

    return size; // return the size of the data
}

void displayData(char country[][MAX_CHAR], double gciNcsiData[][2], int size) {
    cout << setw(20) << left << "Country" << setw(10) << right << "GCI";
    cout << setw(10) << right << "NCSI" << endl;
    cout << "------------------------------------------------" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(20) << left << country[i];
        cout << setw(10) << right << gciNcsiData[i][0];
        cout << setw(10) << right << gciNcsiData[i][1] << endl;
    }
    cout << "------------------------------------------------" << endl;
}

//do summary analysis for max and min GCI
void doAnalysis(char country[][MAX_CHAR], double gciNcsiData[][2], int size) {
    int maxGCI = 0, minGCI = 0;
    for (int i = 0; i < size; i++) {
        if (gciNcsiData[i][0] > gciNcsiData[maxGCI][0]) {
            maxGCI = i;
            country[maxGCI][0] = toupper(country[maxGCI][0]);
        }
        if (gciNcsiData[i][0] < gciNcsiData[minGCI][0]) {
            minGCI = i;
            country[minGCI][0] = tolower(country[minGCI][0]);
        }
    }

    //display the country with the highest and lowest GCI
    cout << "Country with the highest GCI: " << country[maxGCI];
    cout << " with GCI: " << gciNcsiData[maxGCI][0] << endl;
    cout << "Country with the lowest GCI: " << country[minGCI];
    cout << " with GCI: " << gciNcsiData[minGCI][0] << endl;
}

//calculate average of GCI or NCSI
double calcAverage(double gciNcsiData[][2], int count, int column) {
    double sum = 0;
    for (int i = 0; i < count; i++) {
        sum += gciNcsiData[i][column];
    }
    return sum / count;
}

// function to display goodbye message
void goodbye() {
    cout << "Thank you for using the GCI and NCSI data analysis program!" << endl;
    cout << "Goodbye!" << endl;
}