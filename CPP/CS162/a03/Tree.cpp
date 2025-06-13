#include "Tree.h"
#include "List.h"
using namespace std;

Tree::Tree() {
  root = nullptr;
}

Tree::~Tree(){
  cleanup(root);
}

//implement these
bool Tree::compare(Pokemon v1, Pokemon v2){
  return false;
}

bool Tree::compareInt(Pokemon v1, int v2){
  return false;
}

bool Tree::equal(Pokemon v1, Pokemon v2){
  return false;
}

bool Tree::equalInt(Pokemon v1, int v2){
  return false;
}


//implement this, based on the tree's I've showed you
void Tree::cleanup(TNode* t){

}

void Tree::printSorted(){
  printNode(root);
}

//implement this
void Tree::printNode(TNode* t){
  
}

void Tree::insert(Pokemon p){
  root = insertNode(root,p);
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
    if(equal(n->value,p)){

      TNode* newNode = new TNode;
      newNode->value = p;
      newNode->right = nullptr;
      newNode->left = n->left;
      n->left = newNode;
      return n; 
    }
    
    else if(compare(n->value,p)){
      n->left = insertNode(n->left,p);
      return n;
    }
    else{
      n->right = insertNode(n->right,p);
      return n;

    }
  }

}

//implement this!
void Tree::filterLessNode(TNode* t, int v, List &l){
  if(t == nullptr){
    return;
  }
  else {
    if(compareInt(t->value,v)){
      //...
    }
    else {
      //...
    }
  }
}

//implement this!
void Tree::filterMoreNode(TNode* t, int v, List &l){
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
