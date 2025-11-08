#include "table.h"

// Student constructor
Student::Student() : program(nullptr), g_number(nullptr), name(nullptr), standing(0) {}

// Student destructor
Student::~Student() {
    clear();
}

// Copy student data
void Student::copy(const Student& source) {
    clear();
    
    if (source.program) {
        program = new char[strlen(source.program) + 1];
        strcpy(program, source.program);
    }
    
    if (source.g_number) {
        g_number = new char[strlen(source.g_number) + 1];
        strcpy(g_number, source.g_number);
    }
    
    if (source.name) {
        name = new char[strlen(source.name) + 1];
        strcpy(name, source.name);
    }
    
    standing = source.standing;
}

// Clear student data
void Student::clear() {
    delete[] program;
    delete[] g_number;
    delete[] name;
    program = nullptr;
    g_number = nullptr;
    name = nullptr;
    standing = 0;
}

// Node constructor
Node::Node() : next(nullptr) {}

// Node destructor
Node::~Node() {
    // Student destructor will be called automatically
}

// Convert standing to string
const char* standingToString(int standing) {
    switch(standing) {
        case 1: return "unacceptable";
        case 2: return "needs improvement";
        case 3: return "meets expectations";
        case 4: return "exceeds expectations";
        case 5: return "outstanding";
        default: return "unknown";
    }
}

// Table constructor
Table::Table(int size) : table_size(size) {
    table = new Node*[table_size];
    for (int i = 0; i < table_size; ++i) {
        table[i] = nullptr;
    }
}

// Table destructor
Table::~Table() {
    for (int i = 0; i < table_size; ++i) {
        deleteChain(table[i]);
    }
    delete[] table;
}

// Hash function
int Table::hash(const char* key) const {
    int sum = 0;
    for (int i = 0; key[i] != '\0'; ++i) {
        sum += key[i];
    }
    return sum % table_size;
}

// Delete a chain
void Table::deleteChain(Node*& head) {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// Insert a new student
bool Table::insert(const char* program, const char* g_number, 
                   const char* name, int standing) {
    if (!program || !g_number || !name || standing < 1 || standing > 5) {
        return false;
    }
    
    int index = hash(program);
    
    // Create new node
    Node* new_node = new Node();
    
    // Allocate and copy program
    new_node->data.program = new char[strlen(program) + 1];
    strcpy(new_node->data.program, program);
    
    // Allocate and copy g_number
    new_node->data.g_number = new char[strlen(g_number) + 1];
    strcpy(new_node->data.g_number, g_number);
    
    // Allocate and copy name
    new_node->data.name = new char[strlen(name) + 1];
    strcpy(new_node->data.name, name);
    
    new_node->data.standing = standing;
    
    // Insert at beginning of chain
    new_node->next = table[index];
    table[index] = new_node;
    
    return true;
}

// Retrieve all students from a given program
bool Table::retrieve(const char* program, Student all_matches[], int& num_found) {
    if (!program) {
        num_found = 0;
        return false;
    }
    
    int index = hash(program);
    Node* current = table[index];
    num_found = 0;
    
    while (current) {
        if (strcmp(current->data.program, program) == 0) {
            all_matches[num_found].copy(current->data);
            ++num_found;
        }
        current = current->next;
    }
    
    return num_found > 0;
}

// Edit academic standing
bool Table::edit(const char* program, const char* g_number, int new_standing) {
    if (!program || !g_number || new_standing < 1 || new_standing > 5) {
        return false;
    }
    
    int index = hash(program);
    Node* current = table[index];
    
    while (current) {
        if (strcmp(current->data.program, program) == 0 && 
            strcmp(current->data.g_number, g_number) == 0) {
            current->data.standing = new_standing;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Remove all students with unacceptable standing
int Table::remove() {
    int count = 0;
    
    for (int i = 0; i < table_size; ++i) {
        Node* current = table[i];
        Node* prev = nullptr;
        
        while (current) {
            if (current->data.standing == 1) {
                Node* to_delete = current;
                
                if (prev) {
                    prev->next = current->next;
                    current = current->next;
                } else {
                    table[i] = current->next;
                    current = table[i];
                }
                
                delete to_delete;
                ++count;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
    
    return count;
}

// Display all students
void Table::displayAll() const {
    cout << "\n===== ALL STUDENTS =====" << endl;
    int total = 0;
    
    for (int i = 0; i < table_size; ++i) {
        Node* current = table[i];
        while (current) {
            cout << "\nProgram: " << current->data.program << endl;
            cout << "G#: " << current->data.g_number << endl;
            cout << "Name: " << current->data.name << endl;
            cout << "Standing: " << standingToString(current->data.standing) << endl;
            cout << "------------------------" << endl;
            ++total;
            current = current->next;
        }
    }
    
    cout << "\nTotal students: " << total << endl;
}

// Monitor hash table performance
void Table::monitor() const {
    cout << "\n===== HASH TABLE PERFORMANCE =====" << endl;
    cout << "Table Size: " << table_size << endl;
    cout << "\nChain Lengths:" << endl;
    
    int total_items = 0;
    int used_slots = 0;
    int max_chain = 0;
    
    for (int i = 0; i < table_size; ++i) {
        int chain_length = 0;
        Node* current = table[i];
        
        while (current) {
            ++chain_length;
            current = current->next;
        }
        
        if (chain_length > 0) {
            ++used_slots;
            cout << "Index " << i << ": " << chain_length << " item(s)" << endl;
        }
        
        total_items += chain_length;
        if (chain_length > max_chain) {
            max_chain = chain_length;
        }
    }
    
    cout << "\nStatistics:" << endl;
    cout << "Total items: " << total_items << endl;
    cout << "Used slots: " << used_slots << " / " << table_size << endl;
    cout << "Empty slots: " << (table_size - used_slots) << endl;
    cout << "Longest chain: " << max_chain << endl;
    
    if (used_slots > 0) {
        cout << "Average chain length: " 
             << (float)total_items / used_slots << endl;
    }
    
    cout << "Load factor: " 
         << (float)total_items / table_size << endl;
}