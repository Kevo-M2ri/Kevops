#ifndef LIST_H
#define LIST_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

// Pokemon struct
struct Pokemon {
    string name;
    string type1, type2;   // type2 is "" if mono-type
    int hp, attack, defense,
        special_attack, special_defense, speed,
        total;                  // convenience field
    
    // Constructors
    Pokemon();
    Pokemon(string n, string t1, string t2, int h, int att, int def,
            int sp_att, int sp_def, int spd, int tot);
};

// Node for linked list
struct ListNode {
    Pokemon data;
    ListNode* next;
    
    ListNode(Pokemon p);
};

// Linked List class for Pokemon
class PokemonList {
private:
    ListNode* head;
    
    // Helper functions for recursive type-based deletion
    ListNode* deleteStrongToTypeHelper(ListNode* node, const string& type);
    ListNode* deleteWeakToTypeHelper(ListNode* node, const string& type);
    
    // Helper function to check type effectiveness
    bool isStrongAgainst(const Pokemon& pokemon, const string& type);
    bool isWeakAgainst(const Pokemon& pokemon, const string& type);

public:
    // Constructor and Destructor
    PokemonList();
    ~PokemonList();
    
    // Core list operations
    void addToFront(Pokemon pokemon);
    bool deleteByName(const string& name);
    Pokemon* findByName(const string& name);
    
    // Display functions
    void printAll();
    void printByName(const string& name);
    
    // Recursive type-based deletion functions
    void deleteAllStrongToType(const string& type);
    void deleteAllWeakToType(const string& type);
    
    // Utility functions
    bool isEmpty();
    vector<Pokemon> getAllPokemon();
    int size();
};

#endif