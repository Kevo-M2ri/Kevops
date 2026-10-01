/*  Name:    Kelvin Muturi
    Class: CS302
    Degree: Comp Science Major
*/

#include <iostream>
#include <cstring>

using namespace std;


struct Node {
    char* data;
    Node* next;
};

// Traverse to find the last node
Node* findLastNode(Node* head) {
    if (head == nullptr) return nullptr;
    if (head->next == nullptr) return head;
    
    return findLastNode(head->next);
}

// Count how many times a specific string appears in the list
int countOccurrences(Node* head, const char* targetStr) {
    if (head == nullptr) return 0;
    int match = (strcmp(head->data, targetStr) == 0) ? 1 : 0;
    return match + countOccurrences(head->next, targetStr); //recurse rest of list
}

// Find and remove the very last node
int removeLastNodeRecursive(Node*& head) {
    if (head == nullptr) return 0;
    
    // Last node
    if (head->next == nullptr) {
        delete[] head->data; // Free the dynamically allocated character array
        delete head;         // Free the node itself
        head = nullptr;      // Update previous node's next pointer to null
        return 1;            // 1 node was removed
    }
    
    // Move on
    return removeLastNodeRecursive(head->next);
}

// Main Wrapper Function
int removeUniqueLastNode(Node*& head) {
    Node* lastNode = findLastNode(head);
    if (countOccurrences(head, lastNode->data) == 1) {
        return removeLastNodeRecursive(head);
    }
    
    return 0;
}