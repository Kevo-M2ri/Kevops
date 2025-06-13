#include "Map.h"
#include <algorithm>
#include <iostream>
using namespace std;

Map::Map(string description) {
    here = new room;
    here->desc = description;
    here->eastExit = nullptr;
    here->westExit = nullptr;
    here->northExit = nullptr;
    here->southExit = nullptr;
}

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

// Movement functions
void Map::moveEast() {
    if (here->eastExit == nullptr) {
        cout << "You can't go that way!" << endl;
    } else {
        here = here->eastExit;
        printRoom();
    }
}

void Map::moveWest() {
    if (here->westExit == nullptr) {
        cout << "You can't go that way!" << endl;
    } else {
        here = here->westExit;
        printRoom();
    }
}

void Map::moveNorth() {
    if (here->northExit == nullptr) {
        cout << "You can't go that way!" << endl;
    } else {
        here = here->northExit;
        printRoom();
    }
}

void Map::moveSouth() {
    if (here->southExit == nullptr) {
        cout << "You can't go that way!" << endl;
    } else {
        here = here->southExit;
        printRoom();
    }
}

// Room creation functions
void Map::addEast(string description) {
    room* newRoom = new room;
    newRoom->desc = description;
    newRoom->eastExit = nullptr;
    newRoom->westExit = here;  // back link
    newRoom->northExit = nullptr;
    newRoom->southExit = nullptr;

    here->eastExit = newRoom;
}

void Map::addWest(string description) {
    room* newRoom = new room;
    newRoom->desc = description;
    newRoom->eastExit = here;  // back link
    newRoom->westExit = nullptr;
    newRoom->northExit = nullptr;
    newRoom->southExit = nullptr;

    here->westExit = newRoom;
}

void Map::addNorth(string description) {
    room* newRoom = new room;
    newRoom->desc = description;
    newRoom->eastExit = nullptr;
    newRoom->westExit = nullptr;
    newRoom->northExit = nullptr;
    newRoom->southExit = here;  // back link

    here->northExit = newRoom;
}

void Map::addSouth(string description) {
    room* newRoom = new room;
    newRoom->desc = description;
    newRoom->eastExit = nullptr;
    newRoom->westExit = nullptr;
    newRoom->northExit = here;  // back link
    newRoom->southExit = nullptr;

    here->southExit = newRoom;
}

// Room display
void Map::printRoom() {
    cout << "\n" << here->desc << endl;

    // Print exits
    cout << "Exits: ";
    bool hasExits = false;
    if (here->northExit != nullptr) {
        cout << "North ";
        hasExits = true;
    }
    if (here->southExit != nullptr) {
        cout << "South ";
        hasExits = true;
    }
    if (here->eastExit != nullptr) {
        cout << "East ";
        hasExits = true;
    }
    if (here->westExit != nullptr) {
        cout << "West ";
        hasExits = true;
    }
    if (!hasExits) {
        cout << "None";
    }
    cout << endl;

    // Print creatures
    if (!here->mobs.empty()) {
        cout << "Enemies in this room: ";
        for (const auto& creature : here->mobs) {
            cout << creature.getName() << " ";
        }
        cout << endl;
    }

    // Print loot (only if room is cleared)
    if (!here->loot.empty()) {
        if (roomCleared()) {
            cout << "Treasure: ";
            for (const auto& treasure : here->loot) {
                cout << treasure.name << " ";
            }
            cout << endl;
        } else {
            cout << "There appears to be treasure here, but you must defeat the enemies first!" << endl;
        }
    }
}

// Creature management
void Map::addCreature(Creature c) {
    here->mobs.push_back(c);
}

Creature Map::getCreatureForFight() {
    if (!here->mobs.empty()) {
        Creature fighter = here->mobs.back();
        here->mobs.pop_back();
        return fighter;
    }
    return Creature("No Enemy", 0); // return empty creature if none available
}

bool Map::roomCleared() {
    return here->mobs.empty();
}

// Loot management
void Map::addLoot(Treasure t) {
    here->loot.push_back(t);
}

vector<Treasure> Map::getLoot() {
    vector<Treasure> roomLoot = here->loot;
    here->loot.clear(); // remove loot from room
    return roomLoot;
}