#ifndef COURSE_H_
#define COURSE_H_

#include "student.h"

struct Course
{
    Student roaster[20];
    int numStudents;
};

Course initCourse();
Student FindStudentHighestGPA(Course course);
Course AddStudent(Course course, Student student);

#endif // COURSE_H_