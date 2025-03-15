/******************************************************************************
# Author:           Kelvin Muturi
# Lab:              Discussion #5
# Date:             Februrary 24, 2025
# Description:      This program reads data from a file and calculates the
#                   percentages of male and female students in each major.
#                   It also calculates the total number of students and the total
#                   number of students in each major, and the highest paying major
#                   The program then writes the calculated results to an output file.
#                   results to an output file.
# Input:            majorCode, major, majorCategory as character arrays, total, men,
                    women, annualSalary as integers
# Output:           writes Gender distribution by major and overall, totalStudents,
                    and highestPayingMajor to an output file named"stemout.txt"
# Sources:          stem.txt
#******************************************************************************/
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstring>
using namespace std;

const int MAX = 100; // max size of array

// function prototypes
bool openFile(ifstream& inFile, char fileName[]);
void ratioCalc(ifstream& inFile, ofstream& outFile);
void calcTotalStudents(ifstream& inFile, ofstream& outFile);

// main
int main() {
    ifstream inFile; // input file stream
    ofstream outFile; // output file stream
    char fileName[MAX]; // input file name
    char header[MAX];  // header of input file
  
    // get input file name
    cout << "Enter name of input file:";
    cin >> fileName;// get input file name
    
    if (!openFile(inFile, fileName)) {
        cout << "file did not open. Program terminating!!!";
        return 0;
    } //file did not open condition

    outFile.open("stemout.txt"); // output file name

    if (!outFile) {
        cout << "output file did not open. Program terminating!!!";
        inFile.close(); // close input file
        return 0;
    } // output file did not open condition

    inFile.getline(header, MAX); // read header of input file

    ratioCalc(inFile, outFile); // call ratioCalc function

    inFile.clear(); // clear eof flag
    inFile.seekg(0); // set file pointer to beginning of file
    inFile.getline(header, MAX); // read header of input file

    calcTotalStudents(inFile, outFile); // call calcTotalStudents function

    inFile.close(); // close input file
    outFile.close(); // close output file

    return 0;
} // end of main

// function to open file
bool openFile(ifstream &inFile, char fileName[]) {
    inFile.open(fileName);
    if (!inFile) {
        return false; // file did not open
    }
    return true; // file opened successfully
} // end of openFile

// function to calculate ratio of students
void ratioCalc(ifstream& inFile, ofstream& outFile) {
    // declare variables
    char majorCode[MAX];
    char major[MAX];
    char majorCategory[MAX];
    int total;
    int men;
    int women;
    int salary;
    double menPercentage;
    double womenPercentage;

    // output to file
    outFile << "Gender distribution by major" << endl;
    outFile << "--------------------------------" << endl;

    while (inFile >> majorCode >> major >> majorCategory >> total >> men >> women >> salary) {
        if (total > 0) {
            menPercentage = (static_cast<double>(men) / total) * 100; // calculate percentage of men
            womenPercentage = (static_cast<double>(women) / total) * 100; // calculate percentage of women

            outFile << fixed << setprecision(2); // set precision to 2 decimal places
            outFile << left << setw(50) << major
                << "Men: " << menPercentage << setw(7) << "%"
                << "Women: " << womenPercentage << "%" << endl; // output contents to file
        }
    } // end of while loop

    if (!inFile.eof() && inFile.fail()) {
        outFile << "Error reading input file!!" << endl;
    }// finished reading file or error reading file condition

    outFile << endl; // output blank line
}// end of ratioCalc

// function to calculate total number of students
void calcTotalStudents(ifstream& inFile, ofstream& outFile) {
    // declare variables
    char majorCode[MAX];
    char major[MAX];
    char majorCategory[MAX];
    int total;
    int men;
    int women;
    int salary;
    int totalMen = 0;
    int totalWomen = 0;
    int totalStudents = 0;
    char highestPayingMajor[MAX] = " ";
    double totalMenPercentage = 0.0;
    double totalWomenPercentage = 0.0;
    double highestSalary = 0;
    

    while (inFile >> majorCode >>major >> majorCategory >> total >> men >> women >> salary) { // read input file
        totalMen += men;
        totalWomen += women;

        if (salary > highestSalary) {
            highestSalary = salary;
            strcpy(highestPayingMajor, major);
        } // condition to find highest paying major
    }

    totalStudents = totalMen + totalWomen; // calculate total number of students

    if (totalStudents > 0) {
        totalMenPercentage = (static_cast<double>(totalMen) / totalStudents) * 100; // calculate percentage for men
        totalWomenPercentage = (static_cast<double>(totalWomen) / totalStudents) * 100; // calculate percentage for women
    }

    outFile << "Total number of students:" << endl; // header for output of total number of students
    outFile << "--------------------------------" << endl;
    outFile << "Total Students: " << totalStudents << endl;
    outFile << fixed << setprecision(2); // set precision to 2 decimal places
    outFile << "Gender Distribution in general:" << endl; 
    outFile << "Men: " << totalMenPercentage << "%" << endl;
    outFile << "Women: " << totalWomenPercentage << "%" << endl;
    outFile << "Highest paying major is: " << highestPayingMajor << " with  $" << highestSalary << " annual salary" << endl;

    if (!inFile.eof() && inFile.fail()) {
        outFile << "Error reading input file!!" << endl;
    } // finished reading file or error reading file condition
}// end of calcTotalStudents