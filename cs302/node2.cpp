/*  Name:    Kelvin Muturi
    Class: CS302
    Degree: Comp Science Major
*/

#include <iostream>
#include <cstring>

struct Node {
    char* data;
    Node* next;
};

// Count the nodes in the circular linked list
int countNodesRecursive(Node* current, Node* rear) {
    if (current == rear) {
        return 1;
    }
    return 1 + countNodesRecursive(current->next, rear);
}

// Find the node just before the rear and insert the new node
void insertBeforeLastRecursive(Node* current, Node* rear, Node* newNode) {
    if (current->next == rear) {
        current->next = newNode;
        newNode->next = rear;
        return;
    }
    // Keep traversing forward
    insertBeforeLastRecursive(current->next, rear, newNode);
}

// Main Wrapper Function
int insertMovieBeforeLast(Node*& rear) {
    // Create the new node and dynamically allocate character array
    const char* movie = "The Matrix"; 
    Node* newNode = new Node;
    newNode->data = new char[strlen(movie) + 1];
    strcpy(newNode->data, movie);
    
    
    if (rear == nullptr) {
        newNode->next = newNode;
        rear = newNode;
        return 1;
    }
    
    if (rear->next == rear) {
        newNode->next = rear;
        rear->next = newNode;
        return 2;
    }
    
    // Traverse starting from the head (rear->next)
    insertBeforeLastRecursive(rear->next, rear, newNode);
    
    // Count the nodes recursively and return the total size
    return countNodesRecursive(rear->next, rear);
}