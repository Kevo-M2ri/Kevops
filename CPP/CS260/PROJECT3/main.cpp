#include "table.h"

const int MAX_STUDENTS = 100;

// Function prototypes
void displayMenu();
bool loadFromFile(Table& table, const char* filename);
void addStudent(Table& table);
void retrieveStudents(Table& table);
void editStudent(Table& table);
void removeUnacceptable(Table& table);
void clearInputBuffer();

int main() {
    Table table(10);
    
    cout << "========================================" << endl;
    cout << "Student Academic Standing Tracker" << endl;
    cout << "========================================" << endl;
    
    // Load data from file
    cout << "\nLoading data from file..." << endl;
    if (loadFromFile(table, "students.txt")) {
        cout << "Data loaded successfully!" << endl;
    } else {
        cout << "No data file found or file is empty. Starting with empty database." << endl;
    }
    
    int choice;
    bool running = true;
    
    while (running) {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        clearInputBuffer();
        
        switch (choice) {
            case 1:
                addStudent(table);
                break;
            case 2:
                retrieveStudents(table);
                break;
            case 3:
                editStudent(table);
                break;
            case 4:
                removeUnacceptable(table);
                break;
            case 5:
                table.displayAll();
                break;
            case 6:
                table.monitor();
                break;
            case 7:
                cout << "\nThank you for using the Student Tracker!" << endl;
                running = false;
                break;
            default:
                cout << "\nInvalid choice. Please try again." << endl;
        }
        
        if (running) {
            cout << "\nPress Enter to continue...";
            cin.get();
        }
    }
    
    return 0;
}

void displayMenu() {
    cout << "\n========================================" << endl;
    cout << "           MAIN MENU" << endl;
    cout << "========================================" << endl;
    cout << "1. Add a new student" << endl;
    cout << "2. Retrieve students by program" << endl;
    cout << "3. Edit student's academic standing" << endl;
    cout << "4. Remove students with unacceptable standing" << endl;
    cout << "5. Display all students" << endl;
    cout << "6. Monitor hash table performance" << endl;
    cout << "7. Exit" << endl;
    cout << "========================================" << endl;
}

bool loadFromFile(Table& table, const char* filename) {
    ifstream file(filename);
    if (!file) {
        return false;
    }
    
    char program[100];
    char g_number[20];
    char name[100];
    int standing;
    int count = 0;
    
    while (file.getline(program, 100, ',')) {
        file.getline(g_number, 20, ',');
        file.getline(name, 100, ',');
        file >> standing;
        file.ignore(100, '\n');
        
        if (table.insert(program, g_number, name, standing)) {
            ++count;
        }
    }
    
    file.close();
    cout << "Loaded " << count << " student(s) from file." << endl;
    return count > 0;
}

void addStudent(Table& table) {
    char program[100];
    char g_number[20];
    char name[100];
    int standing;
    
    cout << "\n===== ADD NEW STUDENT =====" << endl;
    
    cout << "Enter program name (e.g., Computer Science): ";
    cin.getline(program, 100);
    
    cout << "Enter student G# (e.g., G12345678): ";
    cin.getline(g_number, 20);
    
    cout << "Enter student name (e.g., Jane Doe): ";
    cin.getline(name, 100);
    
    cout << "Enter academic standing (1-5):" << endl;
    cout << "  1 - unacceptable" << endl;
    cout << "  2 - needs improvement" << endl;
    cout << "  3 - meets expectations" << endl;
    cout << "  4 - exceeds expectations" << endl;
    cout << "  5 - outstanding" << endl;
    cout << "Choice: ";
    cin >> standing;
    clearInputBuffer();
    
    if (standing < 1 || standing > 5) {
        cout << "\nInvalid standing. Must be between 1 and 5." << endl;
        return;
    }
    
    if (table.insert(program, g_number, name, standing)) {
        cout << "\nStudent added successfully!" << endl;
    } else {
        cout << "\nFailed to add student." << endl;
    }
}

void retrieveStudents(Table& table) {
    char program[100];
    Student* matches = new Student[MAX_STUDENTS];
    int num_found = 0;
    
    cout << "\n===== RETRIEVE STUDENTS =====" << endl;
    cout << "Enter program name (e.g., Computer Science): ";
    cin.getline(program, 100);
    
    if (table.retrieve(program, matches, num_found)) {
        cout << "\nFound " << num_found << " student(s) in " << program << ":" << endl;
        cout << "========================================" << endl;
        
        for (int i = 0; i < num_found; ++i) {
            cout << "\n[" << (i + 1) << "]" << endl;
            cout << "G#: " << matches[i].g_number << endl;
            cout << "Name: " << matches[i].name << endl;
            cout << "Standing: " << standingToString(matches[i].standing) << endl;
            cout << "------------------------" << endl;
        }
    } else {
        cout << "\nNo students found in program: " << program << endl;
    }
    
    delete[] matches;
}

void editStudent(Table& table) {
    char program[100];
    char g_number[20];
    int new_standing;
    
    cout << "\n===== EDIT STUDENT STANDING =====" << endl;
    cout << "Enter program name (e.g., Computer Science): ";
    cin.getline(program, 100);
    
    cout << "Enter student G# (e.g., G12345678): ";
    cin.getline(g_number, 20);
    
    cout << "Enter new academic standing (1-5):" << endl;
    cout << "  1 - unacceptable" << endl;
    cout << "  2 - needs improvement" << endl;
    cout << "  3 - meets expectations" << endl;
    cout << "  4 - exceeds expectations" << endl;
    cout << "  5 - outstanding" << endl;
    cout << "Choice: ";
    cin >> new_standing;
    clearInputBuffer();
    
    if (new_standing < 1 || new_standing > 5) {
        cout << "\nInvalid standing. Must be between 1 and 5." << endl;
        return;
    }
    
    if (table.edit(program, g_number, new_standing)) {
        cout << "\nStudent's standing updated successfully!" << endl;
    } else {
        cout << "\nStudent not found or update failed." << endl;
    }
}

void removeUnacceptable(Table& table) {
    cout << "\n===== REMOVE UNACCEPTABLE STUDENTS =====" << endl;
    cout << "Are you sure you want to remove all students with" << endl;
    cout << "unacceptable standing? (y/n): ";
    
    char confirm;
    cin >> confirm;
    clearInputBuffer();
    
    if (confirm == 'y' || confirm == 'Y') {
        int count = table.remove();
        cout << "\nRemoved " << count << " student(s) with unacceptable standing." << endl;
    } else {
        cout << "\nOperation cancelled." << endl;
    }
}

void clearInputBuffer() {
    cin.clear();
    cin.ignore(10000, '\n');
}