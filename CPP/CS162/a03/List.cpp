#include "List.h"

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

// fill this in!
void List::cleanup(Node* node){
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