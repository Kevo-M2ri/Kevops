#include "Map.h"
#include <algorithm>
#include <iostream>

Map::~Map() {
    vector<room*> visited;
    deleteRoom(here, visited);
}

// okay here's the neat trick!
// you can potentially have "circular references" in the map
// which means that you need to keep track of pointers you've already
// deleted!
// this means we keep a vector of pointer and stick find in the
// function to make sure that we don't accidentally double clear something
void Map::deleteRoom(room* r, vector<room*>& visited) {
  if (r == nullptr) {
    return;
  } 
  if (find(visited.begin(), visited.end(), r) != visited.end()) {
    return;
  }
  // if we got here we're good to go 
  
  visited.push_back(r);
  
  deleteRoom(r->eastExit, visited);
  deleteRoom(r->westExit, visited);
  deleteRoom(r->northExit, visited);
  deleteRoom(r->southExit, visited);
  
  delete r;
}