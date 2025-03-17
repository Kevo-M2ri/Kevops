/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        March 19, 2025
   Assignment:  CS-161B Assignment a07
   Description: This program reads a list of citizens from a file, allows the
                user to remove a citizen, and displays the updated list. The
                program uses a struct to store citizen data and functions to
                manipulate the data.
   Inputs:      
   Outputs:     updated list of citizens after removal.
   -------------------------------------------------------------------------**/

#include "person.h"

const int MAX_CHAR = 20;

int main() {
    PersonType list[MAX_CHAR];
    int count = 0;
    char fileName[] = "persons.txt";

    cout << "Welcome to the citizen database!" << endl;
    cout << "Here is the list of citizens so far." << endl;

    populatePersons(list, count, fileName); // Populate list from file
    printPersons(list, count); // Print initial list

    // Attempt to remove a person and print updated list if successful  
    if (removePerson(list, count) == true) {
        cout << "Updated list after removal:" << endl;
        printPersons(list, count);
    }
    else {
        cout << "Person not found!" << endl;
    }

    cout << "Thank you for using the citizen database!" << endl;

    return 0;
}