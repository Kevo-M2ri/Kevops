/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        February 2, 2025
   Assignment:  CS-161B Assignment a04
   Description: This program asks the user for input
   Inputs:      num as an integer, 
   Outputs:     encoded file name as a character array.
   -------------------------------------------------------------------------**/

#include <iostream>
#include <limits>
#include <cstring>

using namespace std;

void welcome();
void readInput(char courseNums[][MAXCHAR], int students[], int &count);
void readInt(string prompt, int &num);
void printList(char courseNums[][MAXCHAR], int students[], int &count);
void cancelCourses(char coursenums[][MAXCHAR], int sudents[], int &count);
void goodbye();

const int MAXCHAR = 25;
const int MAXINT = 20;

int main() {
    return 0;
}

void welcome() {
    cout << "Welcome to my double parallel array" << endl;
}

void readInput(char courseNums[][MAXCHAR], int students[], int &count) {
    char tempName[MAXCHAR];
    count = 0;
    string courseStr;
    
    cout << "Enter course number (or 'quit' to end): ";
    cin >> tempName;
    courseStr = tempName;
    for (char &c : courseStr) {
        c = tolower(c);
    }
    
    while (courseStr != "quit") {
        // Read and validate student count
        int studentCount;
        bool validCount = false;
        do {
            readInt("Enter number of students (0-25): ", studentCount);
            if (studentCount >= 0 && studentCount <= 25) {
                validCount = true;
            } else {
                cout << "Error: Number of students must be between 0 and 25.\n";
            }
        } while (!validCount);
        
        // Find insertion position
        int pos = 0;
        while (pos < count && strcmp(courseNums[pos], tempName) < 0) {
            pos++;
        }
        
        // Shift elements to make room for new entry
        for (int i = count; i > pos; i--) {
            strcpy(courseNums[i], courseNums[i-1]);
            students[i] = students[i-1];
        }
        
        // Insert new course and student count
        strcpy(courseNums[pos], tempName);
        students[pos] = studentCount;
        count++;
        
        // Read next course
        cout << "Enter course number (or 'quit' to end): ";
        cin >> tempName;
        courseStr = tempName;
        for (char &c : courseStr) {
            c = tolower(c);
        }
    }
}
void readInt(string prompt, int &num) {
    bool validIntegers = false;

    while (!validIntegers) {
        cout << prompt;
        cin >> num;

        if (cin.fail() || num < 0) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!! Unsupported data entered. Please enter numbers greater than or equal to 0!" << endl;
        }
        validIntegers = true;
    }
}

void printList(char courseNums[][MAXCHAR], int students[], int &count) {
    
}
void cancelCourses(char coursenums[][MAXCHAR], int sudents[], int &count);
void goodbye();