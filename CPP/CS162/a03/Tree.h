#ifndef TREE_H
#define TREE_H

#include "List.h"

// A node in our binary search tree - each node holds one Pokemon
struct TreeNode {
    Pokemon pokemon;     // The Pokemon data
    TreeNode* left;      // Points to left child (smaller values)
    TreeNode* right;     // Points to right child (larger values)

    // Constructor - creates a new tree node with the given Pokemon
    TreeNode(Pokemon p);
};

// Our binary search tree class that stores Pokemon
// This tree sorts Pokemon by their TOTAL STATS (you can change this!)
class PokemonTree {
private:
    TreeNode* root;  // Points to the root node (or nullptr if tree is empty)

    // Helper functions for recursion (these are private - only used inside the class)
    TreeNode* insertHelper(TreeNode* node, Pokemon p);
    void printHelper(TreeNode* node);
    void deleteTreeHelper(TreeNode* node);
    void filterHelper(TreeNode* node, int value, string operation, PokemonList& result);

    // Function to get the value we're sorting by (CHANGE THIS to sort by different stats)
    int getSortValue(const Pokemon& p);

public:
    // Constructor - creates an empty tree
    PokemonTree();

    // Destructor - cleans up all memory when the tree is destroyed
    ~PokemonTree();

    // Add a Pokemon to the tree (it will be inserted in the right place automatically)
    void insert(Pokemon p);

    // Print all Pokemon in the tree in sorted order (smallest to largest)
    void printInOrder();

    // Find all Pokemon with stats LESS THAN OR EQUAL TO the given value
    PokemonList findLessOrEqual(int value);

    // Find all Pokemon with stats GREATER THAN OR EQUAL TO the given value  
    PokemonList findGreaterOrEqual(int value);

    // Find all Pokemon with stats EXACTLY EQUAL TO the given value
    PokemonList findEqual(int value);

    // Check if the tree is empty
    bool isEmpty();

    // Get a description of what we're sorting by
    string getSortDescription();
};

#endif