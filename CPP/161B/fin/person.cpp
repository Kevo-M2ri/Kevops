#include "person.h"

// Function to read from file and populate the list
void populatePersons(PersonType list[], int& count, const char fileName[]) {
    ifstream inFile;
    char name[MAX_CHAR];
    char citizen[MAX_CHAR];
    int age = 0;

    inFile.open(fileName);
    if (!inFile) {
        cerr << "Failed to open " << fileName << " to populate inventory!" << endl;
        exit(1);
    }

    inFile >> name;
    while (!inFile.eof()) {
        inFile >> citizen >> age;
        strcpy(list[count].name, name);
        strcpy(list[count].citizenship, citizen);
        list[count].age = age;
        count++;

        inFile >> name;
    }
    inFile.close();
}

void printPersons(const PersonType list[], int count) {
    cout << left; // Align text to the left

    // Print the header with proper column spacing
    cout << setw(20) << "Name" 
         << setw(20) << "Citizenship" 
         << setw(5) << "Age" << endl;

    // Print a separator line using std::string
    cout << string(45, '-') << endl;

    // Print each person's details without numbering
    for (int index = 0; index < count; index++) {
        cout << setw(20) << list[index].name
             << setw(20) << list[index].citizenship
             << setw(5) << list[index].age << endl;
    }
}

int compareIgnoreCase(const char s1[], const char s2[]) {
    int i = 0;

    while (s1[i] != '\0' && s2[i] != '\0') {
        char c1 = tolower(static_cast<unsigned char>(s1[i]));
        char c2 = tolower(static_cast<unsigned char>(s2[i]));

        if (c1 != c2) {
            return c1 - c2;
        }

        i++;
    }

    // Check if one string is longer than the other
    return tolower(static_cast<unsigned char>(s1[i])) - tolower(static_cast<unsigned char>(s2[i]));
}

// Function to remove a person by name (case-insensitive)
bool removePerson(PersonType list[], int &count) {
    char srchName[MAX_CHAR];
    int foundIndex = -1; // Index of the person to be removed

    cout << "Enter the name to remove: ";
    cin.clear(); // Clear any error flags
    cin.ignore(cin.rdbuf()->in_avail()); // Clear the input buffer
    cin.getline(srchName, MAX_CHAR);

    // Search for the person's index (case-insensitive comparison)
    for (int i = 0; i < count; i++) {
        if (compareIgnoreCase(list[i].name, srchName) == 0) {
            foundIndex = i;
            break; // Stop once we find the person
        }
    }

    if (foundIndex != -1) {
        // Shift elements left to remove the found person
        for (int i = foundIndex; i < count - 1; i++) {
            strcpy(list[i].name, list[i+1].name);
            strcpy(list[i].citizenship, list[i+1].citizenship);
            list[i].age = list[i+1].age;
        }
        count--; // Reduce count after removal

        return true; // Indicate that removal was successful
    }

    return false; // Indicate that no person was found
}