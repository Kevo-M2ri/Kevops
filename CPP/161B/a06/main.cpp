#include <iostream>
#include <cstring>
#include <fstream>
#include "Student.h"
#include "Course.h"

using namespace std;
int main() {
	Course course = initCourse();
	ifstream inFile;
  	char lastname[20];

  	cout << "Welcome to my Course Roster Program\n" << endl;

 	inFile.open("students.txt");
  	if(!inFile)
  	{
    	cout << "File did not open! Program Exiting!!" << endl;
    	return 0;
  	}

  	readStudent(inFile, course);
  	inFile.close();

  	cout << "Here is the course roster: " << endl;
  	printRoster(course);

  	cout << "\nPlease enter the last name of the student you would like to drop: ";
  	cin >> lastname;
  	dropStudent(lastname, course);

  	cout << "\nHere is the course roster: " << endl;
  	printRoster(course);

  	Student student = findStudentHighestGPA(course);
  	cout << "\nStudent with the highest GPA: " << endl;
  	printStd(student);

  	cout << "Thank you for using my Student Roster program!!" << endl;
  
	return 0;
}