#include "engineerlist.h"

// Constructor
EngineerList::EngineerList() : head(nullptr), size(0) {}

// Copy constructor
EngineerList::EngineerList(const EngineerList& other) : head(nullptr), size(0) {
    Node* current = other.head;
    while (current) {
        addEngineer(new Engineer(current->data));
        current = current->next;
    }
}

// Assignment operator
EngineerList& EngineerList::operator=(const EngineerList& other) {
    if (this != &other) {
        clearList();
        Node* current = other.head;
        while (current) {
            addEngineer(new Engineer(*(current->data)));
            current = current->next;
        }
    }
    return *this;
}

// Destructor
EngineerList::~EngineerList() {
    clearList();
}

// Helper function to clear the list
void EngineerList::clearList() {
    while (head){
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    size = 0;
}

// find insertion point for sorted order
Node* EngineerList::findInsertionPoint(const Engineer& eng) const {
    if (!head || eng < *(head->data)) {
        return nullptr; // Insert at the beginning
    }

    Node* current = head;
    while (current->next && *(current->next->data) < eng) {
        current = current->next;
    }
    return current; // Return the node after which to insert
}

// Add engineer to the list
bool EngineerList::addEngineer(Engineer* eng) {
    if (!eng) return false; // Null check

    Node* newNode = new Node(eng);

    // Empty list case or insert at the beginning
    if (!head || *eng < *(head->data)) {
        newNode->next = head;
        head = newNode;
    } else {
        Node* prev = findInsertionPoint(*eng);
        newNode->next = prev->next;
        prev->next = newNode;
    }

    size++;
    return true;
}

// Promote engineer at index
bool EngineerList::promoteEngineer(int index) {
    if (index < 0 || index >= size) return false; // Index out of bounds

    Node* current = head;
    for (int i = 0; i < index && current; i++) {
        current = current->next;
    }

    if (current && current->data) {
        int currentLevel = current->data->getTitleLevel();
        if (currentLevel < MAX_TITLE_LENGTH) {
            current->data->setTitleLevel(currentLevel + 1);
            return true;
        }
    }
    return false; // Cannot promote
}

// Edit assessment of engineer at index
bool EngineerList::editAssessment(int index, AssessmentLevel newLevel) {
    if (index < 0 || index >= size) return false; // Index out of bounds

    Node* current = head;
    for (int i = 0; i < index && current; i++) {
        current = current->next;
    }

    if (current && current->data) {
        current->data->setAssessment(newLevel);
        return true;
    }
    return false; // Invalid index
}

// Display all engineers
void EngineerList::displayAll() const {
    if (size == 0) {
        cout << "No engineers in the list." << endl;
        return;
    }

    Node* current = head;
    int index = 0;
    while (current) {
        cout << "[" << index << "] ";
        current->data->displayInfo();
        cout << endl;
        current = current->next;
        index++;
    }
}



// Helper function for recursive display by level
void EngineerList::displayLevelRecursive(Node* current, int targetLevel) const {
    if (!current) return;

    if (current->data->getTitleLevel() == targetLevel) {
        current->data->displayInfo();
        cout << endl;
    }

    displayLevelRecursive(current->next, targetLevel);
}

// Display engineers by title level
void EngineerList::displayByLevel(int level) const {
    if (level < MIN_TITLE_LENGTH || level > MAX_TITLE_LENGTH) {
        cout << "Title level must be between " << MIN_TITLE_LENGTH << " and " << MAX_TITLE_LENGTH << "." << endl;
        return;
    }

    cout << "Engineers at Level L" << level << ":" << endl;
    bool found = false;
    Node* current = head;

    while (current) {
        if (current->data->getTitleLevel() == level) {
            current->data->displayInfo();
            cout << endl;
            found = true;
        }
        current = current->next;
    }

    if(!found) {
        cout << "No engineers found at Level L" << level << "." << endl;
    }
}

// Helper function for recursive removal by assessment level
void EngineerList::removeByAssessmentRecursive(Node*& current, AssessmentLevel targetLevel) {
    if (!current) return;

    removeByAssessmentRecursive(current->next, targetLevel);

    if (current->data->getAssessment() == targetLevel) {
        Node* temp = current;
        current = current->next;
        delete temp;
        size--;
    }
}

// Remove engineers by assessment level(recursive)
int EngineerList::removeByAssessment(AssessmentLevel targetLevel) {
    int initialSize = size;
    removeByAssessmentRecursive(head, targetLevel);
    return initialSize - size; // Return number of removed engineers
}

// Get engineer at index
const Engineer* EngineerList::getEngineerAt(int index) const {
    ifstream file(filename);
    if (!file.is_open()) {
        return false; // File could not be opened
    }

    char first[50], last[50];
    int title, assess;

    while (file >> first >> last >> title >> assess) {
        if (title >= MIN_TITLE_LENGTH && title <= MAX_TITLE_LENGTH &&
            assess >= UNACCEPTABLE && assess <= OUTSTANDING) {
            addEngineer(new Engineer(first, last, title, static_cast<AssessmentLevel>(assess)));
        }
    }

    file.close();
    return true; // Successfully loaded
}