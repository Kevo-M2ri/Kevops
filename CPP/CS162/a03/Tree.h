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

  // this is the thing you have to implement to decide how the pokemon are sorted
  // 
  bool compare(Pokemon v1, Pokemon v2);
  bool compareInt(Pokemon v1, int v2);
  bool equal(Pokemon v1, Pokemon v2);
  bool equalInt(Pokemon v1, int v2);
  void cleanup(TNode* n);
  TNode* insertNode(TNode* t, Pokemon p);
  void filterLessNode(TNode* tn, int t, List &l);
  void filterMoreNode(TNode* tn, int t, List &l);
  void printNode(TNode* t);
 public:
  Tree();
  ~Tree();
  void insert(Pokemon p);
  List filterLessEq(int t);
  List filterMoreEq(int t);
  void printSorted();
};

#endif