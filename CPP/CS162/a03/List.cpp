#include "List.h"

using namespace std;

// Pokemon constructors
Pokemon::Pokemon() : hp(0), attack(0), defense(0), special_attack(0), 
                     special_defense(0), speed(0), total(0) {}

Pokemon::Pokemon(string n, string t1, string t2, int h, int att, int def,
                 int sp_att, int sp_def, int spd, int tot) 
    : name(n), type1(t1), type2(t2), hp(h), attack(att), defense(def),
      special_attack(sp_att), special_defense(sp_def), speed(spd), total(tot) {}

// ListNode constructor
ListNode::ListNode(Pokemon p) : data(p), next(nullptr) {}

// PokemonList constructor and destructor
PokemonList::PokemonList() : head(nullptr) {}

PokemonList::~PokemonList() {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Add pokemon to front of list
void PokemonList::addToFront(Pokemon pokemon) {
    ListNode* newNode = new ListNode(pokemon);
    newNode->next = head;
    head = newNode;
}

// Delete pokemon by name (delete anywhere in list)
bool PokemonList::deleteByName(const string& name) {
    if (head == nullptr) return false;
    
    // If head needs to be deleted
    if (head->data.name == name) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
        return true;
    }
    
    // Search for the pokemon to delete
    ListNode* current = head;
    while (current->next != nullptr) {
        if (current->next->data.name == name) {
            ListNode* temp = current->next;
            current->next = current->next->next;
            delete temp;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Find pokemon by name
Pokemon* PokemonList::findByName(const string& name) {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->data.name == name) {
            return &(current->data);
        }
        current = current->next;
    }
    return nullptr;
}

// Print all pokemon in the list
void PokemonList::printAll() {
    if (head == nullptr) {
        cout << "List is empty." << endl;
        return;
    }
    
    ListNode* current = head;
    int count = 1;
    while (current != nullptr) {
        cout << count << ". " << current->data.name << " (" << current->data.type1;
        if (!current->data.type2.empty()) {
            cout << "/" << current->data.type2;
        }
        cout << ") - Total: " << current->data.total << endl;
        current = current->next;
        count++;
    }
}

// Print specific pokemon by name
void PokemonList::printByName(const string& name) {
    Pokemon* p = findByName(name);
    if (p != nullptr) {
        cout << p->name << " (" << p->type1;
        if (!p->type2.empty()) {
            cout << "/" << p->type2;
        }
        cout << ")" << endl;
        cout << "  HP: " << p->hp << " | ATK: " << p->attack << " | DEF: " << p->defense << endl;
        cout << "  SpA: " << p->special_attack << " | SpD: " << p->special_defense 
             << " | Speed: " << p->speed << endl;
        cout << "  Total: " << p->total << endl;
    } else {
        cout << "Pokemon not found: " << name << endl;
    }
}

// Type effectiveness helper functions
bool PokemonList::isStrongAgainst(const Pokemon& pokemon, const string& type) {
    // Simplified type chart - expand as needed
    string pType1 = pokemon.type1;
    string pType2 = pokemon.type2;
    
    // Water beats Fire and Ground and Rock
    if ((pType1 == "Water" || pType2 == "Water") && 
        (type == "Fire" || type == "Ground" || type == "Rock")) return true;
    
    // Fire beats Grass, Ice, Bug, Steel
    if ((pType1 == "Fire" || pType2 == "Fire") && 
        (type == "Grass" || type == "Ice" || type == "Bug" || type == "Steel")) return true;
    
    // Grass beats Water, Ground, Rock
    if ((pType1 == "Grass" || pType2 == "Grass") && 
        (type == "Water" || type == "Ground" || type == "Rock")) return true;
    
    // Electric beats Water and Flying
    if ((pType1 == "Electric" || pType2 == "Electric") && 
        (type == "Water" || type == "Flying")) return true;
    
    // Fighting beats Normal, Rock, Steel, Ice, Dark
    if ((pType1 == "Fighting" || pType2 == "Fighting") && 
        (type == "Normal" || type == "Rock" || type == "Steel" || type == "Ice" || type == "Dark")) return true;
    
    // Add more type matchups as needed
    return false;
}

bool PokemonList::isWeakAgainst(const Pokemon& pokemon, const string& type) {
    // Reverse of strong against
    string pType1 = pokemon.type1;
    string pType2 = pokemon.type2;
    
    // Fire is weak to Water, Ground, Rock
    if ((pType1 == "Fire" || pType2 == "Fire") && 
        (type == "Water" || type == "Ground" || type == "Rock")) return true;
    
    // Water is weak to Grass and Electric
    if ((pType1 == "Water" || pType2 == "Water") && 
        (type == "Grass" || type == "Electric")) return true;
    
    // Grass is weak to Fire, Ice, Poison, Flying, Bug
    if ((pType1 == "Grass" || pType2 == "Grass") && 
        (type == "Fire" || type == "Ice" || type == "Poison" || type == "Flying" || type == "Bug")) return true;
    
    // Flying is weak to Electric, Ice, Rock
    if ((pType1 == "Flying" || pType2 == "Flying") && 
        (type == "Electric" || type == "Ice" || type == "Rock")) return true;
    
    // Ground is weak to Water, Grass, Ice
    if ((pType1 == "Ground" || pType2 == "Ground") && 
        (type == "Water" || type == "Grass" || type == "Ice")) return true;
    
    return false;
}

// Recursive helper for deleting pokemon strong to a type
ListNode* PokemonList::deleteStrongToTypeHelper(ListNode* node, const string& type) {
    if (node == nullptr) return nullptr;
    
    // Recursively process the rest of the list first
    node->next = deleteStrongToTypeHelper(node->next, type);
    
    // Check if current pokemon is strong against the given type
    if (isStrongAgainst(node->data, type)) {
        ListNode* temp = node;
        node = node->next;
        delete temp;
    }
    
    return node;
}

// Recursive helper for deleting pokemon weak to a type
ListNode* PokemonList::deleteWeakToTypeHelper(ListNode* node, const string& type) {
    if (node == nullptr) return nullptr;
    
    // Recursively process the rest of the list first
    node->next = deleteWeakToTypeHelper(node->next, type);
    
    // Check if current pokemon is weak against the given type
    if (isWeakAgainst(node->data, type)) {
        ListNode* temp = node;
        node = node->next;
        delete temp;
    }
    
    return node;
}

// Delete all pokemon strong to given type (recursive)
void PokemonList::deleteAllStrongToType(const string& type) {
    head = deleteStrongToTypeHelper(head, type);
}

// Delete all pokemon weak to given type (recursive)
void PokemonList::deleteAllWeakToType(const string& type) {
    head = deleteWeakToTypeHelper(head, type);
}

// Check if list is empty
bool PokemonList::isEmpty() {
    return head == nullptr;
}

// Get all pokemon as vector (for writing to file)
vector<Pokemon> PokemonList::getAllPokemon() {
    vector<Pokemon> result;
    ListNode* current = head;
    while (current != nullptr) {
        result.push_back(current->data);
        current = current->next;
    }
    return result;
}

// Get size of list
int PokemonList::size() {
    int count = 0;
    ListNode* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}