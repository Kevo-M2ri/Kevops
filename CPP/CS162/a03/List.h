#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Simple Pokemon struct to hold all the data
struct Pokemon {
    string name;
    string type1, type2;   // type2 is empty "" if Pokemon has only one type
    int hp, attack, defense, special_attack, special_defense, speed, total;

    // Simple constructor - sets everything to default values
    Pokemon();

    // Constructor with all values
    Pokemon(string n, string t1, string t2, int h, int att, int def,
            int sp_att, int sp_def, int spd, int tot);
};

// A node in our linked list - each node holds one Pokemon
struct Node {
    Pokemon pokemon;    // The Pokemon data
    Node* next;         // Pointer to the next node (or nullptr if this is the last)

    // Constructor - creates a new node with the given Pokemon
    Node(Pokemon p);
};

// Our linked list class that stores Pokemon
class PokemonList {
private:
    Node* head;  // Points to the first node in the list (or nullptr if empty)

    // Helper functions for recursion (these are private - only used inside the class)
    Node* deleteStrongHelper(Node* current, const string& type);
    Node* deleteWeakHelper(Node* current, const string& type);

    // Helper functions to check type effectiveness
    bool pokemonStrongAgainst(const Pokemon& p, const string& type);
    bool pokemonWeakAgainst(const Pokemon& p, const string& type);

public:
    // Constructor - creates an empty list
    PokemonList();

    // Destructor - cleans up all memory when the list is destroyed
    ~PokemonList();

    // Add a Pokemon to the front of the list
    void addToFront(Pokemon p);

    // Find a Pokemon by name - returns a pointer to it (or nullptr if not found)
    Pokemon* findByName(const string& name);

    // Delete a Pokemon by name - returns true if found and deleted
    bool deleteByName(const string& name);

    // Print information about a specific Pokemon
    void printByName(const string& name);

    // Print all Pokemon in the list
    void printAll();

    // Recursive functions to delete Pokemon based on type effectiveness
    void deleteAllStrongTo(const string& type);
    void deleteAllWeakTo(const string& type);

    // Check if the list is empty
    bool isEmpty();

    // Get the number of Pokemon in the list
    int getSize();

    // Get all Pokemon as a vector (for saving to file)
    vector<Pokemon> getAllPokemon();
};

#endif