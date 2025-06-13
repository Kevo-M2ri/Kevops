#include "List.h"

// Pokemon constructors
Pokemon::Pokemon() {
    // Set all numbers to 0 and strings to empty
    name = "";
    type1 = "";
    type2 = "";
    hp = attack = defense = special_attack = special_defense = speed = total = 0;
}

Pokemon::Pokemon(string n, string t1, string t2, int h, int att, int def,
                 int sp_att, int sp_def, int spd, int tot) {
    name = n;
    type1 = t1;
    type2 = t2;
    hp = h;
    attack = att;
    defense = def;
    special_attack = sp_att;
    special_defense = sp_def;
    speed = spd;
    total = tot;
}

// Node constructor
Node::Node(Pokemon p) {
    pokemon = p;    // Store the Pokemon data
    next = nullptr; // This node doesn't point to anything yet
}

// PokemonList constructor - create an empty list
PokemonList::PokemonList() {
    head = nullptr;  // Empty list - head points to nothing
}

// PokemonList destructor - VERY IMPORTANT for memory management!
PokemonList::~PokemonList() {
    // We need to delete every node to free memory
    while (head != nullptr) {
        Node* nodeToDelete = head;    // Remember which node to delete
        head = head->next;            // Move head to the next node
        delete nodeToDelete;          // Free the memory (DYNAMIC MEMORY DEALLOCATION)
    }
    // Now head is nullptr and all memory is freed
}

// Add a Pokemon to the front of the list
void PokemonList::addToFront(Pokemon p) {
    // Step 1: Create a new node (DYNAMIC MEMORY ALLOCATION)
    Node* newNode = new Node(p);

    // Step 2: Make the new node point to what head was pointing to
    newNode->next = head;

    // Step 3: Make head point to the new node
    head = newNode;

    // Now the new node is at the front of the list!
}

// Find a Pokemon by name
Pokemon* PokemonList::findByName(const string& name) {
    // Start at the beginning of the list
    Node* current = head;

    // Walk through the list until we find the Pokemon or reach the end
    while (current != nullptr) {
        if (current->pokemon.name == name) {
            // Found it! Return a pointer to the Pokemon data
            return &(current->pokemon);
        }
        current = current->next;  // Move to the next node
    }

    // Didn't find it - return nullptr
    return nullptr;
}

// Delete a Pokemon by name
bool PokemonList::deleteByName(const string& name) {
    // Case 1: Empty list
    if (head == nullptr) {
        return false;  // Can't delete from empty list
    }

    // Case 2: The first Pokemon is the one we want to delete
    if (head->pokemon.name == name) {
        Node* nodeToDelete = head;    // Remember which node to delete
        head = head->next;            // Move head to the next node
        delete nodeToDelete;          // Free the memory
        return true;
    }

    // Case 3: The Pokemon is somewhere else in the list
    Node* current = head;
    while (current->next != nullptr) {
        if (current->next->pokemon.name == name) {
            // Found it! The next node is the one to delete
            Node* nodeToDelete = current->next;     // Remember which node to delete
            current->next = current->next->next;    // Skip over the node we're deleting
            delete nodeToDelete;                    // Free the memory
            return true;
        }
        current = current->next;  // Keep looking
    }

    // Didn't find it
    return false;
}

// Print information about a specific Pokemon
void PokemonList::printByName(const string& name) {
    Pokemon* p = findByName(name);
    if (p != nullptr) {
        cout << "=== " << p->name << " ===" << endl;
        cout << "Type: " << p->type1;
        if (!p->type2.empty()) {
            cout << "/" << p->type2;
        }
        cout << endl;
        cout << "HP: " << p->hp << "  Attack: " << p->attack << "  Defense: " << p->defense << endl;
        cout << "Sp.Atk: " << p->special_attack << "  Sp.Def: " << p->special_defense << "  Speed: " << p->speed << endl;
        cout << "Total Stats: " << p->total << endl;
    } else {
        cout << "Pokemon '" << name << "' not found in the list." << endl;
    }
}

// Print all Pokemon in the list
void PokemonList::printAll() {
    if (head == nullptr) {
        cout << "The list is empty - no Pokemon to show." << endl;
        return;
    }

    cout << "=== ALL POKEMON IN LIST ===" << endl;
    Node* current = head;
    int count = 1;

    while (current != nullptr) {
        cout << count << ". " << current->pokemon.name;
        cout << " (" << current->pokemon.type1;
        if (!current->pokemon.type2.empty()) {
            cout << "/" << current->pokemon.type2;
        }
        cout << ") - Total: " << current->pokemon.total << endl;

        current = current->next;
        count++;
    }
    cout << "Total Pokemon: " << (count - 1) << endl;
}

// Helper function: Check if a Pokemon is strong against a type
bool PokemonList::pokemonStrongAgainst(const Pokemon& p, const string& type) {
    // This is a simplified type chart - in real Pokemon there are 18 types!
    // Water beats Fire, Ground, Rock
    if ((p.type1 == "Water" || p.type2 == "Water") && 
        (type == "Fire" || type == "Ground" || type == "Rock")) {
        return true;
    }

    // Fire beats Grass, Ice, Bug, Steel  
    if ((p.type1 == "Fire" || p.type2 == "Fire") && 
        (type == "Grass" || type == "Ice" || type == "Bug" || type == "Steel")) {
        return true;
    }

    // Grass beats Water, Ground, Rock
    if ((p.type1 == "Grass" || p.type2 == "Grass") && 
        (type == "Water" || type == "Ground" || type == "Rock")) {
        return true;
    }

    // Electric beats Water, Flying
    if ((p.type1 == "Electric" || p.type2 == "Electric") && 
        (type == "Water" || type == "Flying")) {
        return true;
    }

    return false;  // Not strong against this type
}

// Helper function: Check if a Pokemon is weak against a type  
bool PokemonList::pokemonWeakAgainst(const Pokemon& p, const string& type) {
    // Fire is weak to Water, Ground, Rock
    if ((p.type1 == "Fire" || p.type2 == "Fire") && 
        (type == "Water" || type == "Ground" || type == "Rock")) {
        return true;
    }

    // Water is weak to Grass, Electric
    if ((p.type1 == "Water" || p.type2 == "Water") && 
        (type == "Grass" || type == "Electric")) {
        return true;
    }

    // Grass is weak to Fire, Ice, Poison, Flying, Bug
    if ((p.type1 == "Grass" || p.type2 == "Grass") && 
        (type == "Fire" || type == "Ice" || type == "Poison" || type == "Flying" || type == "Bug")) {
        return true;
    }

    return false;  // Not weak against this type
}

// RECURSIVE helper function to delete Pokemon strong against a type
Node* PokemonList::deleteStrongHelper(Node* current, const string& type) {
    // Base case: If we've reached the end of the list, we're done
    if (current == nullptr) {
        return nullptr;
    }

    // Recursive step: Process the rest of the list first
    current->next = deleteStrongHelper(current->next, type);

    // Now decide what to do with the current node
    if (pokemonStrongAgainst(current->pokemon, type)) {
        // This Pokemon should be deleted
        Node* nodeToDelete = current;
        current = current->next;  // Skip this node
        delete nodeToDelete;      // Free the memory
    }

    return current;  // Return the (possibly new) head of this part of the list
}

// RECURSIVE helper function to delete Pokemon weak against a type
Node* PokemonList::deleteWeakHelper(Node* current, const string& type) {
    // Base case: If we've reached the end of the list, we're done
    if (current == nullptr) {
        return nullptr;
    }

    // Recursive step: Process the rest of the list first
    current->next = deleteWeakHelper(current->next, type);

    // Now decide what to do with the current node
    if (pokemonWeakAgainst(current->pokemon, type)) {
        // This Pokemon should be deleted
        Node* nodeToDelete = current;
        current = current->next;  // Skip this node
        delete nodeToDelete;      // Free the memory
    }

    return current;  // Return the (possibly new) head of this part of the list
}

// Delete all Pokemon that are strong against the given type (RECURSIVE)
void PokemonList::deleteAllStrongTo(const string& type) {
    cout << "Deleting all Pokemon strong against " << type << " type..." << endl;
    head = deleteStrongHelper(head, type);
}

// Delete all Pokemon that are weak against the given type (RECURSIVE)
void PokemonList::deleteAllWeakTo(const string& type) {
    cout << "Deleting all Pokemon weak against " << type << " type..." << endl;
    head = deleteWeakHelper(head, type);
}

// Check if the list is empty
bool PokemonList::isEmpty() {
    return head == nullptr;
}

// Count how many Pokemon are in the list
int PokemonList::getSize() {
    int count = 0;
    Node* current = head;

    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}

// Get all Pokemon as a vector (useful for saving to a file)
vector<Pokemon> PokemonList::getAllPokemon() {
    vector<Pokemon> result;
    Node* current = head;

    while (current != nullptr) {
        result.push_back(current->pokemon);
        current = current->next;
    }

    return result;
}