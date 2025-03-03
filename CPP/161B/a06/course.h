//The Course struct that uses the Student struct to create a list of students.
#ifndef COURSE_H_
#define COURSE_H_

#include "student.h"
#include <fstream>

using namespace std;

struct Course {
	Student roster[20];
	int numStudents;
};

Course initCourse();
Course addStudent(Student student, Course &course);
void readStudent(ifstream &inFile, Course &course);
void dropStudent(char *lastname, Course &course);
Student findStudentHighestGPA(Course course);
void printRoster(Course course);

#endif