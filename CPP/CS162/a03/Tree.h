#ifndef TREE_H
#define TREE_H

#include "List.h"

using namespace std;

// Node for binary search tree
struct TreeNode {
    Pokemon data;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(Pokemon p);
};

// Binary Search Tree class for Pokemon
// This tree is sorted by TOTAL stats (you can change this by modifying the comparison)
class PokemonBST {
private:
    TreeNode* root;
    
    // Helper functions for tree operations
    TreeNode* insertHelper(TreeNode* node, Pokemon pokemon);
    void printInOrderHelper(TreeNode* node);
    void filterHelper(TreeNode* node, int value, char operation, PokemonList& result);
    void destroyTree(TreeNode* node);
    
    // Function to get the sorting key (change this to use different stat)
    int getSortingKey(const Pokemon& pokemon);

public:
    // Constructor and Destructor
    PokemonBST();
    ~PokemonBST();
    
    // Core tree operations
    void insert(Pokemon pokemon);
    void printInOrder();
    
    // Filter functions that return linked lists
    PokemonList filterLessThanOrEqual(int value);
    PokemonList filterGreaterThanOrEqual(int value);
    PokemonList filterEqual(int value);
    
    // Utility functions
    bool isEmpty();
    string getSortingCriterion();
};

#endif