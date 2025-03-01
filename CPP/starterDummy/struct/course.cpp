#include <iostream>
#include <cstring>
#include "course.h"

using namespace std;

Course initCourse()
{
    Course course;
    course.numStudents = 0;
    return course;
}

Student FindStudentHighestGPA(Course course)
{
    Student topStudent = course.roaster[0];
    double maxGPA = GetGPA(topStudent);
    double tempGPA = 0;

    for (int i = 1; i < course.numStudents; i++) {
    tempGPA = GetGPA(course.roaster[i]);
        if (tempGPA > maxGPA)
        {
            maxGPA = tempGPA;
            topStudent = course.roaster[i];
        }
    }
    return topStudent;
}