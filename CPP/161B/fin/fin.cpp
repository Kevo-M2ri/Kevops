/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        March 19, 2025
   Assignment:  CS-161B Assignment final
   Description: This program reads a list of citizens from a file, allows the
                user to remove a citizen, and displays the updated list. The
                program uses a struct to store citizen data and functions to
                manipulate the data.
   Inputs:      list of citizens from a file, name of citizen to remove.
   Outputs:     updated list of citizens after removal.
   -------------------------------------------------------------------------**/

#include "person.h"

int main() {
    PersonType list[MAX_CHAR];
    int count = 0;
    char fileName[] = "persons.txt";
    char outputFileName[] = "output.txt";

    cout << "Welcome to the citizen database!" << endl;
    cout << "Here is the list of citizens so far." << endl << endl;

    populatePersons(list, count, fileName); // Populate list from file
    printPersons(list, count); // Print initial list
    writeToFile(list, count, outputFileName); // Write to file

    // Attempt to remove a person and print updated list if successful  
    if (removePerson(list, count) == true) {
        cout << "\nUpdated list after removal:" << endl;
        printPersons(list, count);
        writeToFile(list, count, outputFileName); // Write to file
        cout << "\nPerson removed successfully! Check " << outputFileName << " for updated list." << endl;
    }
    else {
        cout << "Person not found!" << endl;
    }

    cout << "\nThank you for using the citizen database!" << endl;
    cout << "Output has been written to " << outputFileName << endl;

    return 0;
}