//struct for PersonType
#pragma once
#include <iostream>
#include <cstring>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

const int MAX_CHAR = 101;

struct PersonType {
  char name[MAX_CHAR];
  char citizenship[MAX_CHAR];
  int age;
};

//function prototypes
void populatePersons(PersonType list[], int& count, const char fileName[]);
void printPersons(const PersonType list[], int count);
bool removePerson(PersonType list[], int& count);
int compareIgnoreCase(const char str1[], const char str2[]);