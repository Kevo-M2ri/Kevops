#include "Tree.h"
#include "List.h"
#include <iostream>
using namespace std;

Tree::Tree() {
    root = nullptr;
}

Tree::~Tree(){
    cleanup(root);
}

// I'm choosing to sort by TOTAL stats as the key
// You can change this to any other numeric field (hp, attack, defense, etc.)

bool Tree::compare(Pokemon v1, Pokemon v2){
    return v1.total < v2.total;  // v1 is less than v2
}

bool Tree::compareInt(Pokemon v1, int v2){
    return v1.total < v2;  // v1's total is less than the integer value
}

bool Tree::equal(Pokemon v1, Pokemon v2){
    return v1.total == v2.total;  // Equal total stats
}

bool Tree::equalInt(Pokemon v1, int v2){
    return v1.total == v2;  // Pokemon's total equals the integer value
}

// Recursively cleanup all nodes in the tree
void Tree::cleanup(TNode* t){
    if (t == nullptr) {
        return;
    }
    cleanup(t->left);
    cleanup(t->right);
    delete t;
}

void Tree::printSorted(){
    printNode(root);
}

// In-order traversal to print nodes in sorted order
void Tree::printNode(TNode* t){
    if (t == nullptr) {
        return;
    }
    
    printNode(t->left);   // Print left subtree first
    
    // Print current node
    Pokemon p = t->value;
    cout << p.name << " (" << p.type1;
    if (!p.type2.empty()) {
        cout << "/" << p.type2;
    }
    cout << ") - Total: " << p.total << endl;
    
    printNode(t->right);  // Print right subtree
}

void Tree::insert(Pokemon p){
    root = insertNode(root, p);
}

Tree::TNode* Tree::insertNode(Tree::TNode* n, Pokemon p){
    if(n == nullptr){
        TNode* newNode = new TNode;
        newNode->value = p;
        newNode->left = nullptr;
        newNode->right = nullptr;
        return newNode;
    }
    else{
        if(equal(n->value, p)){
            // For equal values, insert to the left (to handle duplicates)
            TNode* newNode = new TNode;
            newNode->value = p;
            newNode->right = nullptr;
            newNode->left = n->left;
            n->left = newNode;
            return n; 
        }
        else if(compare(p, n->value)){  // p < n->value, go left
            n->left = insertNode(n->left, p);
            return n;
        }
        else{  // p > n->value, go right
            n->right = insertNode(n->right, p);
            return n;
        }
    }
}

// Filter nodes with values <= v
void Tree::filterLessNode(TNode* t, int v, List &l){
    if(t == nullptr){
        return;
    }
    
    if(compareInt(t->value, v) || equalInt(t->value, v)){
        // This node's value is <= v, so include it and search both subtrees
        l.addToFront(t->value);
        filterLessNode(t->left, v, l);
        filterLessNode(t->right, v, l);
    }
    else {
        // This node's value is > v, so only search left subtree
        filterLessNode(t->left, v, l);
    }
}

// Filter nodes with values >= v
void Tree::filterMoreNode(TNode* t, int v, List &l){
    if(t == nullptr){
        return;
    }
    
    if(!compareInt(t->value, v)){
        // This node's value is >= v, so include it and search both subtrees
        l.addToFront(t->value);
        filterMoreNode(t->left, v, l);
        filterMoreNode(t->right, v, l);
    }
    else {
        // This node's value is < v, so only search right subtree
        filterMoreNode(t->right, v, l);
    }
}

// Filter nodes with values exactly equal to v
void Tree::filterEqualNode(TNode* t, int v, List &l){
    if(t == nullptr){
        return;
    }
    
    if(equalInt(t->value, v)){
        l.addToFront(t->value);
    }
    
    // Continue searching both subtrees since equal values might be anywhere
    filterEqualNode(t->left, v, l);
    filterEqualNode(t->right, v, l);
}

List Tree::filterMoreEq(int v){
    List l;
    filterMoreNode(root, v, l);
    return l;
}

List Tree::filterLessEq(int v){
    List l;
    filterLessNode(root, v, l);
    return l;
}

List Tree::filterEqual(int v){
    List l;
    filterEqualNode(root, v, l);
    return l;
}

string Tree::getSortDescription(){
    return "total stats";  // Describe what we're sorting by
}