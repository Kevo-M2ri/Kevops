#include <iostream>
#include <cstring>

#include "course.h"
#include "student.h"

using namespace std;

int main() {
    Course course = initCourse();

    Student student1 = InitStudent("John", "Doe", 3.5);
    Student student2 = InitStudent("Jane", "Smith", 3.8);
    Student student3 = InitStudent("Tom", "Brown", 3.2);
    Student student4 = InitStudent("Alice", "Green", 3.9);

    course = AddStudent(course, student1);
    course = AddStudent(course, student2);
    course = AddStudent(course, student3);
    course = AddStudent(course, student4);

    Student topStudent = FindStudentHighestGPA(course);
    
    char studentName[20];
    GetLastName(topStudent, studentName);

    cout << "The student with the highest GPA is: " << studentName << endl;

    return 0;
}