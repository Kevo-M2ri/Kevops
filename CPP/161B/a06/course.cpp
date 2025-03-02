//The implementation file for Course.h
//It loads students from a text file.
#include <iostream>
#include <cstring>
#include <fstream>
#include "Course.h"
#include "Student.h"

using namespace std;

//initiaizes a course variable and returns it. The array is empty
//and the number of students is set to 0.
Course initCourse() {
	Course course;
	course.numStudents = 0;
	return course;
}

//reads a student from the file and calls AddStudent
void readStudent(ifstream &inFile, Course &course) {
    Student student;
    char first[20];
    char last[20];
    double gpa;

    while (!inFile.eof()) {
        inFile >> first >> last >> gpa;
        student = initStudent(first, last, gpa);
        addStudent(student, course);
    }
}

//adds a student to the roster, and increment count
//modify this function to add the student sorted by name
//do not use any sorting functions.
//See this example in zyBooks Section 14.7 [https://learn.zybooks.com/zybook/PCCCS161BSpring23/chapter/14/section/7]
void addStudent(Student student, Course &course) {
	course.roster[course.numStudents].gpa = student.gpa;
	strcpy(course.roster[course.numStudents].last, student.last);
	strcpy(course.roster[course.numStudents].first, student.first);
	course.numStudents++;
}

//prints a whole Course roster calling student print.
//use a for loop and print all the students
//must call the printStd function in Student.h
void printRoster(Course course)
{
    for(int i = 0; i < course.numStudents; i++)
    {
        printStd(course.roster[i]);
    }
}

void dropStudent(char *lastname, Course &course) {
    int i = 0;
    while (i < course.numStudents) {
        if (strcmp(course.roster[i].last, lastname) == 0) {
            for (int j = i; j < course.numStudents - 1; j++) {
                course.roster[j] = course.roster[j + 1];
            }
            course.numStudents--;
        } else {
            i++;
        }
    }
}
Student findStudentHighestGPA(Course course) {
    Student highest = course.roster[0];
    for (int i = 1; i < course.numStudents; i++) {
        if (course.roster[i].gpa > highest.gpa) {
            highest = course.roster[i];
        }
    }
    return highest;
}