#ifndef STUDENT_H_
#define STUDENT_H_

struct Student
{
    char first[20];
    char last[20];
    double gpa;
};

Student InitStudent(const char *first, const char *last, double gpa);
void GetLastName(Student student, char *studentName);
double GetGPA(Student student);

#endif // STUDENT_H_