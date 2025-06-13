// Complete List.cpp implementation

#include "List.h"
#include <iostream>

// Constructor
List::List() {
    n = nullptr;
}

// Destructor
List::~List() {
    cleanup(n);
}

// Copy constructor - performs deep copy
List::List(const List& other) {
    n = nullptr;
    if (other.n == nullptr) {
        return;
    }

    // We need to copy the list in the same order
    // Since this is a singly linked list, we'll copy recursively
    n = copyHelper(other.n);
}

// Assignment operator
List& List::operator=(const List& other) {
    if (this != &other) {
        // Clean up existing nodes
        cleanup(n);
        n = nullptr;

        // Copy from other
        if (other.n != nullptr) {
            n = copyHelper(other.n);
        }
    }
    return *this;
}

// Cleanup function - recursively delete all nodes
void List::cleanup(Node* node) {
    if (node == nullptr) {
        return;
    }
    cleanup(node->tail);  // First clean up the rest of the list
    delete node;          // Then delete this node
}

// Helper function for deep copy
List::Node* List::copyHelper(Node* other) {
    if (other == nullptr) {
        return nullptr;
    }

    Node* newNode = new Node;
    newNode->head = other->head;  // Copy the Pokemon data
    newNode->tail = copyHelper(other->tail);  // Recursively copy the rest
    return newNode;
}

// Add Pokemon to front of list
void List::addToFront(Pokemon p) {
    Node* newNode = new Node;
    newNode->head = p;
    newNode->tail = n;
    n = newNode;
}

// Remove Pokemon by position (0-indexed)
void List::remove(int pos) {
    if (pos < 0 || n == nullptr) {
        return;
    }

    if (pos == 0) {
        Node* temp = n;
        n = n->tail;
        delete temp;
        return;
    }

    // Find the node before the one we want to remove
    Node* current = n;
    for (int i = 0; i < pos - 1 && current->tail != nullptr; i++) {
        current = current->tail;
    }

    if (current->tail != nullptr) {
        Node* nodeToDelete = current->tail;
        current->tail = nodeToDelete->tail;
        delete nodeToDelete;
    }
}

// Remove Pokemon by name
void List::remove(string name) {
    if (n == nullptr) {
        return;
    }

    // If first node matches
    if (n->head.name == name) {
        Node* temp = n;
        n = n->tail;
        delete temp;
        return;
    }

    // Search for the node to remove
    Node* current = n;
    while (current->tail != nullptr && current->tail->head.name != name) {
        current = current->tail;
    }

    if (current->tail != nullptr) {
        Node* nodeToDelete = current->tail;
        current->tail = nodeToDelete->tail;
        delete nodeToDelete;
    }
}

// Get Pokemon by position
Pokemon List::get(int pos) {
    if (pos < 0 || n == nullptr) {
        return Pokemon(); // Return default Pokemon if invalid
    }

    Node* current = n;
    for (int i = 0; i < pos && current != nullptr; i++) {
        current = current->tail;
    }

    if (current != nullptr) {
        return current->head;
    }
    return Pokemon(); // Return default if not found
}

// Get Pokemon by name
Pokemon List::get(string name) {
    Node* current = n;
    while (current != nullptr) {
        if (current->head.name == name) {
            return current->head;
        }
        current = current->tail;
    }
    return Pokemon(); // Return default if not found
}

// Print all Pokemon in the list
void List::printList() {
    if (n == nullptr) {
        cout << "List is empty." << endl;
        return;
    }

    Node* current = n;
    int count = 1;
    while (current != nullptr) {
        Pokemon p = current->head;
        cout << count << ". " << p.name << " (" << p.type1;
        if (!p.type2.empty()) {
            cout << "/" << p.type2;
        }
        cout << ") - HP:" << p.hp << " ATK:" << p.attack << " DEF:" << p.defense 
             << " Total:" << p.total << endl;
        current = current->tail;
        count++;
    }
}

// Recursively filter out Pokemon weak to a given type
void List::filterByWeak(string aType) {
    filterWeakHelper(n, aType);
}

// Helper function for filtering weak Pokemon
void List::filterWeakHelper(Node*& node, string aType) {
    if (node == nullptr) {
        return;
    }

    if (node->head.isWeakTo(aType)) {
        Node* temp = node;
        node = node->tail;
        delete temp;
        filterWeakHelper(node, aType); // Continue with next node
    } else {
        filterWeakHelper(node->tail, aType); // Move to next node
    }
}

// Recursively filter out Pokemon strong to a given type
void List::filterByStrong(string aType) {
    filterStrongHelper(n, aType);
}

// Helper function for filtering strong Pokemon
void List::filterStrongHelper(Node*& node, string aType) {
    if (node == nullptr) {
        return;
    }

    if (node->head.isStrongTo(aType)) {
        Node* temp = node;
        node = node->tail;
        delete temp;
        filterStrongHelper(node, aType); // Continue with next node
    } else {
        filterStrongHelper(node->tail, aType); // Move to next node
    }
}