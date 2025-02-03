/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        February 2, 2025
   Assignment:  CS-161B Assignment a04
   Description: This program asks the user to input a list of course numbers and
                the number of students enrolled in each course. The program then
                prints the list of courses and the number of students enrolled in
                each course. It then cancels courses with less than 10 students
                enrolled and prints the list of courses after cancelling some.
   Inputs:      num as an integer, courseNums as a character array, students as
                an integer array, count as an integer.
   Outputs:     courseNums and students as arrays before and after cancelling
                courses with less than 10 students, count as an integer.
   -------------------------------------------------------------------------**/

#include <iostream>
#include <limits>
#include <cstring>
#include <iomanip>
using namespace std;

// constants definitions
const int MINSTUDENTS = 10;
const int MAXSTUDENTS = 25;
const int MAXCOURSES = 20;
const int MAXCHAR = 51;

// functions declarations
void welcome();
void readInput(char courseNums[][MAXCHAR], int students[], int &count);
void readInt(string prompt, int &num);
void printList(char courseNums[][MAXCHAR], int students[], int &count);
void cancelCourses(char coursenums[][MAXCHAR], int sudents[], int &count);
void goodbye();

// function main
int main() {
    // variables declarations 
    char courseNums[MAXCOURSES][MAXCHAR];
    int students[MAXCOURSES];
    int count = 0;

    welcome(); // welcome message and banner

    readInput(courseNums, students, count); // function to read inputs for the arrays from the user

    cout << "\n\tCourses before cancelling" << endl;
    cout << "-----------------------------------------" << endl; //for separating output parts
    printList(courseNums, students, count); // print info for all courses

    cancelCourses(courseNums, students, count); // cancel courses wiht below 10 students

    cout << "\n\tCourses after cancelling some" << endl;
    cout << "---------------------------------------------" << endl; //for separating output parts
    printList(courseNums, students, count); // print courses after cancelling some

    return 0;
} //function main()

void welcome() {
    cout << "Welcome to my Course Enrollment and Cancellation program!!" << endl;
    cout << "You can only enter up to " << MAXCOURSES << " courses." << endl;
    cout << "Courses that have a student enrollment lower than " << MINSTUDENTS << " will be dropped!" << endl << endl;
} // function welcome()

void readInput(char courseNums[][MAXCHAR], int students[], int &count) {
    // variables declarations and initializations
    string courseStr;
    int studentCount;
    int pos = 0;
    count = 0;
    
    while(count < MAXCOURSES) { //count cannot exceed maximum number of courses
        cout << "Enter course number (or 'quit' to end): ";
        cin >> courseStr;

        for (char &c : courseStr) c = tolower(c); //converting all course name alphabets to lower case

        if (courseStr == "quit" || courseStr == "Quit" || courseStr == "QUIT") {
            return;
        } // exit condition
        
        readInt("Enter the number of students(0 - 25):", studentCount); //reading number of students in a course
        while (studentCount < 0 || studentCount > MAXSTUDENTS) {
            readInt("Enter the number of students(0 - 25):", studentCount);
        }
        
        while (pos < count && strcmp(courseNums[pos], courseStr.c_str()) < 0) {
            pos++;
        } // correct position to insert new course into courseNums array found

        for(int i = count; i > pos; i--) {
            strcpy(courseNums[i], courseNums[i - 1]); // 
            students[i] = students[i - 1];
        } // elements shifted to make room for new entry

        // insert new course and student count in the room made
        strcpy(courseNums[pos], courseStr.c_str());
        students[pos] = studentCount;
        count++;
    }
}

void readInt(string prompt, int &num) {
    bool validIntegers = false;

    while (!validIntegers) {
        cout << prompt;
        cin >> num;

        if (cin.fail() || num < 0 || num > MAXSTUDENTS) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error!! Unsupported data entered. Please enter numbers greater than or equal to 0!" << endl;
        } // error message and failed input condition
        else {
            validIntegers = true;
        }
    } // input has been validated
}

void printList(char courseNums[][MAXCHAR], int students[], int &count) {
    if (count == 0) {
        cout << "No courses available." << endl;
        return;
    } // no courses condition

    cout << "\n-----------------------------------" << endl; //elements to print separation
    cout << left << setw(10) << "COURSE NUMBER" << right << setw(20) << "STUDENTS ENROLLED" << endl;
    cout << "-----------------------------------" << endl; //elements to print separation

    for (int i = 0; i < count; i++) {
        cout << " " << left << setw(5) << courseNums[i] << right << setw(15) << students[i] << endl;
    } // printing courses and students enrolled

    cout << "------------------------------------" << endl; //elements to print separation

}

void cancelCourses(char courseNums[][MAXCHAR], int students[], int &count) {
    int newCount = 0; // variable definition
    for (int i = 0; i < count; i++) {
        if (students[i] >= MINSTUDENTS) {
            strcpy(courseNums[newCount], courseNums[i]);
            students[newCount] = students[i];
            newCount++;
        }
    } //courses wit less than 10 students cancelled

    count = newCount;
}

void goodbye() {
    cout << "\nThank you for using my program! Have a good one!" << endl;
}// goodbye message