#include <iostream>
#include <cstring>
#include "student.h"

using namespace std;

Student InitStudent(const char *first, const char *last, double gpa)
{
    Student student;
    strcpy(student.first, first);
    strcpy(student.last, last);
    student.gpa = gpa;
    return student;
}

void GetLastName(Student student, char *studentName)
{
    strcpy(studentName, student.last);
}

double GetGPA(Student student)
{
    return student.gpa;
}