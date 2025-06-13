#include "Tree.h"

// TreeNode constructor
TreeNode::TreeNode(Pokemon p) {
    pokemon = p;        // Store the Pokemon data
    left = nullptr;     // No left child yet
    right = nullptr;    // No right child yet
}

// PokemonTree constructor - create an empty tree
PokemonTree::PokemonTree() {
    root = nullptr;  // Empty tree - root points to nothing
}

// PokemonTree destructor - VERY IMPORTANT for memory management!
PokemonTree::~PokemonTree() {
    deleteTreeHelper(root);  // Delete all nodes starting from the root
}

// Helper function to delete all nodes in the tree (RECURSIVE)
void PokemonTree::deleteTreeHelper(TreeNode* node) {
    if (node != nullptr) {
        // Delete left subtree first
        deleteTreeHelper(node->left);
        // Delete right subtree
        deleteTreeHelper(node->right);
        // Now delete this node (DYNAMIC MEMORY DEALLOCATION)
        delete node;
    }
}

// Function to get the value we use for sorting
// CHANGE THIS LINE to sort by different Pokemon stats!
int PokemonTree::getSortValue(const Pokemon& p) {
    return p.total;  // Currently sorting by total stats

    // Uncomment one of these to sort by different stats:
    // return p.speed;           // Sort by speed
    // return p.attack;          // Sort by attack power  
    // return p.defense;         // Sort by defense
    // return p.hp;              // Sort by hit points
    // return p.special_attack;  // Sort by special attack
    // return p.special_defense; // Sort by special defense
}

// Helper function to insert a Pokemon into the tree (RECURSIVE)
TreeNode* PokemonTree::insertHelper(TreeNode* node, Pokemon p) {
    // Base case: If we've found an empty spot, create a new node here
    if (node == nullptr) {
        return new TreeNode(p);  // DYNAMIC MEMORY ALLOCATION
    }

    // Recursive case: Decide whether to go left or right
    int newValue = getSortValue(p);
    int currentValue = getSortValue(node->pokemon);

    if (newValue <= currentValue) {
        // New Pokemon goes on the left (smaller or equal values)
        node->left = insertHelper(node->left, p);
    } else {
        // New Pokemon goes on the right (larger values)
        node->right = insertHelper(node->right, p);
    }

    return node;  // Return the unchanged node
}

// Insert a Pokemon into the tree
void PokemonTree::insert(Pokemon p) {
    root = insertHelper(root, p);
}

// Helper function to print the tree in sorted order (RECURSIVE)
void PokemonTree::printHelper(TreeNode* node) {
    if (node != nullptr) {
        // First, print everything in the left subtree (smaller values)
        printHelper(node->left);

        // Then, print this node
        cout << node->pokemon.name;
        cout << " (" << node->pokemon.type1;
        if (!node->pokemon.type2.empty()) {
            cout << "/" << node->pokemon.type2;
        }
        cout << ") - " << getSortDescription() << ": " << getSortValue(node->pokemon) << endl;

        // Finally, print everything in the right subtree (larger values)
        printHelper(node->right);
    }
}

// Print all Pokemon in the tree in sorted order
void PokemonTree::printInOrder() {
    if (root == nullptr) {
        cout << "The tree is empty - no Pokemon to show." << endl;
        return;
    }

    cout << "=== ALL POKEMON IN TREE (SORTED) ===" << endl;
    printHelper(root);
}

// Helper function to filter Pokemon based on a condition (RECURSIVE)
void PokemonTree::filterHelper(TreeNode* node, int value, string operation, PokemonList& result) {
    if (node == nullptr) {
        return;  // Base case: reached the end of this branch
    }

    int nodeValue = getSortValue(node->pokemon);
    bool matches = false;

    // Check if this Pokemon matches our condition
    if (operation == "<=") {
        matches = (nodeValue <= value);
    } else if (operation == ">=") {
        matches = (nodeValue >= value);
    } else if (operation == "==") {
        matches = (nodeValue == value);
    }

    // If it matches, add it to our result list
    if (matches) {
        result.addToFront(node->pokemon);
    }

    // Always check both left and right subtrees
    // (We need to check everywhere because we want ALL matches, not just some)
    filterHelper(node->left, value, operation, result);
    filterHelper(node->right, value, operation, result);
}

// Find all Pokemon with stats less than or equal to the given value
PokemonList PokemonTree::findLessOrEqual(int value) {
    PokemonList result;  // Create an empty list to store results
    filterHelper(root, value, "<=", result);
    return result;
}

// Find all Pokemon with stats greater than or equal to the given value
PokemonList PokemonTree::findGreaterOrEqual(int value) {
    PokemonList result;  // Create an empty list to store results
    filterHelper(root, value, ">=", result);
    return result;
}

// Find all Pokemon with stats exactly equal to the given value
PokemonList PokemonTree::findEqual(int value) {
    PokemonList result;  // Create an empty list to store results
    filterHelper(root, value, "==", result);
    return result;
}

// Check if the tree is empty
bool PokemonTree::isEmpty() {
    return root == nullptr;
}

// Get a description of what we're sorting by
string PokemonTree::getSortDescription() {
    return "Total Stats";  // Change this if you change getSortValue()

    // Match this with the getSortValue function:
    // return "Speed";
    // return "Attack";
    // return "Defense"; 
    // return "HP";
    // return "Special Attack";
    // return "Special Defense";
}