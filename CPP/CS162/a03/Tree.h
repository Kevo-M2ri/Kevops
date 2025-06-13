#ifndef TREE_H
#define TREE_H

#include "List.h"
#include "Pokemon.h"

class Tree{
 private:
  struct TNode{
    TNode* left;
    TNode* right;
    Pokemon value;
  };

  TNode* root;

  // Comparison functions - these determine how Pokemon are sorted
  // Currently set to sort by total stats, but you can change this
  bool compare(Pokemon v1, Pokemon v2);     // v1 < v2
  bool compareInt(Pokemon v1, int v2);      // v1's key < v2
  bool equal(Pokemon v1, Pokemon v2);       // v1 == v2
  bool equalInt(Pokemon v1, int v2);        // v1's key == v2

  void cleanup(TNode* n);
  TNode* insertNode(TNode* t, Pokemon p);
  void filterLessNode(TNode* tn, int t, List &l);
  void filterMoreNode(TNode* tn, int t, List &l);
  void filterEqualNode(TNode* tn, int t, List &l);
  void printNode(TNode* t);

 public:
  Tree();
  ~Tree();
  void insert(Pokemon p);
  List filterLessEq(int t);
  List filterMoreEq(int t);
  List filterEqual(int t);
  void printSorted();
  std::string getSortDescription();  // Returns description of sort key
};

#endif