#ifndef LIST_H
#define LIST_H

#include "Pokemon.h"

class List {
 private:
  struct Node {
    Pokemon head;
    Node* tail;
  };

  Node* n;

  /*
    Helper functions for recursive implementations
   */
  Node* copyHelper(Node* other);  // Helper for deep copy
  void cleanup(Node* other);      // Cleanup all nodes recursively
  void filterWeakHelper(Node*& node, string aType);   // Helper for filtering weak Pokemon
  void filterStrongHelper(Node*& node, string aType); // Helper for filtering strong Pokemon
  
 public:
  List();
  ~List();
  List(const List& other);  // Copy constructor
  List& operator=(const List& other);  // Assignment operator
  
  void addToFront(Pokemon p);
  void remove(int n);
  void remove(string name);
  Pokemon get(int n);
  Pokemon get(string name);
  void printList();
  void filterByWeak(string aType);
  void filterByStrong(string aType);
};
#endif