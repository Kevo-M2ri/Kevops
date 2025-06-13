#include "Tree.h"

using namespace std;

// TreeNode constructor
TreeNode::TreeNode(Pokemon p) : data(p), left(nullptr), right(nullptr) {}

// PokemonBST constructor and destructor
PokemonBST::PokemonBST() : root(nullptr) {}

PokemonBST::~PokemonBST() {
    destroyTree(root);
}

// Get the sorting key for comparison (CHANGE THIS TO USE DIFFERENT STAT)
int PokemonBST::getSortingKey(const Pokemon& pokemon) {
    // Currently sorting by TOTAL stats
    return pokemon.total;
    
    // Uncomment one of these lines to sort by different stats:
    // return pokemon.speed;        // Sort by speed
    // return pokemon.attack;       // Sort by attack
    // return pokemon.defense;      // Sort by defense
    // return pokemon.hp;           // Sort by HP
    // return pokemon.special_attack;    // Sort by special attack
    // return pokemon.special_defense;   // Sort by special defense
}

// Helper function to insert pokemon into tree
TreeNode* PokemonBST::insertHelper(TreeNode* node, Pokemon pokemon) {
    if (node == nullptr) {
        return new TreeNode(pokemon);
    }
    
    // Compare using the sorting key
    if (getSortingKey(pokemon) <= getSortingKey(node->data)) {
        node->left = insertHelper(node->left, pokemon);
    } else {
        node->right = insertHelper(node->right, pokemon);
    }
    
    return node;
}

// Insert pokemon into the tree
void PokemonBST::insert(Pokemon pokemon) {
    root = insertHelper(root, pokemon);
}

// Helper function to print tree in sorted order
void PokemonBST::printInOrderHelper(TreeNode* node) {
    if (node != nullptr) {
        printInOrderHelper(node->left);
        cout << node->data.name << " (" << node->data.type1;
        if (!node->data.type2.empty()) {
            cout << "/" << node->data.type2;
        }
        cout << ") - Total: " << getSortingKey(node->data) << endl;
        printInOrderHelper(node->right);
    }
}

// Print all pokemon in sorted order
void PokemonBST::printInOrder() {
    if (root == nullptr) {
        cout << "Tree is empty." << endl;
        return;
    }
    printInOrderHelper(root);
}

// Helper function to filter pokemon based on criteria
void PokemonBST::filterHelper(TreeNode* node, int value, char operation, PokemonList& result) {
    if (node == nullptr) return;
    
    int nodeValue = getSortingKey(node->data);
    bool matches = false;
    
    switch (operation) {
        case 'L': // Less than or equal
            if (nodeValue <= value) matches = true;
            break;
        case 'G': // Greater than or equal
            if (nodeValue >= value) matches = true;
            break;
        case 'E': // Equal
            if (nodeValue == value) matches = true;
            break;
    }
    
    if (matches) {
        result.addToFront(node->data);
    }
    
    // Always check both subtrees for filtering
    filterHelper(node->left, value, operation, result);
    filterHelper(node->right, value, operation, result);
}

// Filter pokemon with sorting key <= value
PokemonList PokemonBST::filterLessThanOrEqual(int value) {
    PokemonList result;
    filterHelper(root, value, 'L', result);
    return result;
}

// Filter pokemon with sorting key >= value
PokemonList PokemonBST::filterGreaterThanOrEqual(int value) {
    PokemonList result;
    filterHelper(root, value, 'G', result);
    return result;
}

// Filter pokemon with sorting key == value
PokemonList PokemonBST::filterEqual(int value) {
    PokemonList result;
    filterHelper(root, value, 'E', result);
    return result;
}

// Helper function to destroy the tree
void PokemonBST::destroyTree(TreeNode* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}

// Check if tree is empty
bool PokemonBST::isEmpty() {
    return root == nullptr;
}

// Get description of sorting criterion
string PokemonBST::getSortingCriterion() {
    return "Total Stats"; // Change this if you change the sorting key
    
    // Match this with the getSortingKey function:
    // return "Speed";
    // return "Attack";
    // return "Defense";
    // return "HP";
    // return "Special Attack";
    // return "Special Defense";
}