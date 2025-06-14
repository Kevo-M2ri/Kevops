#include "Map.h"
#include <algorithm>
#include <iostream>
using namespace std;

/**
 * Constructor - Creates the initial starting room
 * Initializes the map with a single room and sets it as the current location
 * 
 * @param description Text description of the starting room
 */
Map::Map(string description) {
    here = new room;                    // Create starting room
    here->desc = description;           // Set room description
    // Initialize all exits to null (no connections yet)
    here->eastExit = nullptr;
    here->westExit = nullptr;
    here->northExit = nullptr;
    here->southExit = nullptr;
}

/**
 * Destructor - Cleans up all dynamically allocated room memory
 * Uses recursive deletion to properly clean up the entire map structure
 * while avoiding infinite loops from circular references
 */
Map::~Map() {
    vector<room*> visited;              // Track visited rooms to prevent cycles
    deleteRoom(here, visited);          // Start recursive deletion from current room
}

/**
 * Recursively deletes all rooms in the map structure
 * Uses a visited list to handle potential circular references between rooms
 * 
 * @param r Pointer to the room to delete
 * @param visited Reference to vector tracking already visited rooms
 */
void Map::deleteRoom(room* r, vector<room*>& visited) {
    // Base cases: null room or already visited room
    if (r == nullptr) return;
    if (find(visited.begin(), visited.end(), r) != visited.end()) return;

    // Mark this room as visited
    visited.push_back(r);
    
    // Recursively delete all connected rooms
    deleteRoom(r->eastExit, visited);
    deleteRoom(r->westExit, visited);
    deleteRoom(r->northExit, visited);
    deleteRoom(r->southExit, visited);

    // Delete this room after processing all connections
    delete r;
}

/**
 * Moves the player to the east room if possible
 * Prints an error message if no east exit exists
 * Automatically displays the new room description upon successful movement
 */
void Map::moveEast() {
    if (here->eastExit == nullptr) {
        cout << "You can't go that way!" << endl;
    } else {
        here = here->eastExit;          // Update current location
        printRoom();                    // Show new room description
    }
}

/**
 * Moves the player to the west room if possible
 * Prints an error message if no west exit exists
 * Automatically displays the new room description upon successful movement
 */
void Map::moveWest() {
    if (here->westExit == nullptr) {
        cout << "You can't go that way!" << endl;
    } else {
        here = here->westExit;          // Update current location
        printRoom();                    // Show new room description
    }
}

/**
 * Moves the player to the north room if possible
 * Prints an error message if no north exit exists
 * Automatically displays the new room description upon successful movement
 */
void Map::moveNorth() {
    if (here->northExit == nullptr) {
        cout << "You can't go that way!" << endl;
    } else {
        here = here->northExit;         // Update current location
        printRoom();                    // Show new room description
    }
}

/**
 * Moves the player to the south room if possible
 * Prints an error message if no south exit exists
 * Automatically displays the new room description upon successful movement
 */
void Map::moveSouth() {
    if (here->southExit == nullptr) {
        cout << "You can't go that way!" << endl;
    } else {
        here = here->southExit;         // Update current location
        printRoom();                    // Show new room description
    }
}

/**
 * Creates a new room to the east of the current room
 * Establishes bidirectional links between the current room and new room
 * 
 * @param description Text description for the new room
 */
void Map::addEast(string description) {
    room* newRoom = new room;           // Allocate new room
    newRoom->desc = description;        // Set room description
    newRoom->eastExit = nullptr;        // Initialize exits
    newRoom->westExit = here;           // Link back to current room
    newRoom->northExit = nullptr;
    newRoom->southExit = nullptr;

    here->eastExit = newRoom;           // Link current room to new room
}

/**
 * Creates a new room to the west of the current room
 * Establishes bidirectional links between the current room and new room
 * 
 * @param description Text description for the new room
 */
void Map::addWest(string description) {
    room* newRoom = new room;           // Allocate new room
    newRoom->desc = description;        // Set room description
    newRoom->eastExit = here;           // Link back to current room
    newRoom->westExit = nullptr;        // Initialize exits
    newRoom->northExit = nullptr;
    newRoom->southExit = nullptr;

    here->westExit = newRoom;           // Link current room to new room
}

/**
 * Creates a new room to the north of the current room
 * Establishes bidirectional links between the current room and new room
 * 
 * @param description Text description for the new room
 */
void Map::addNorth(string description) {
    room* newRoom = new room;           // Allocate new room
    newRoom->desc = description;        // Set room description
    newRoom->eastExit = nullptr;        // Initialize exits
    newRoom->westExit = nullptr;
    newRoom->northExit = nullptr;
    newRoom->southExit = here;          // Link back to current room

    here->northExit = newRoom;          // Link current room to new room
}

/**
 * Creates a new room to the south of the current room
 * Establishes bidirectional links between the current room and new room
 * 
 * @param description Text description for the new room
 */
void Map::addSouth(string description) {
    room* newRoom = new room;           // Allocate new room
    newRoom->desc = description;        // Set room description
    newRoom->eastExit = nullptr;        // Initialize exits
    newRoom->westExit = nullptr;
    newRoom->northExit = here;          // Link back to current room
    newRoom->southExit = nullptr;

    here->southExit = newRoom;          // Link current room to new room
}

/**
 * Displays comprehensive information about the current room
 * Shows room description, available exits, enemies, and treasure
 * Treasure is only shown if all enemies in the room have been defeated
 */
void Map::printRoom() {
    // Safety check for null room pointer
    if (here == nullptr) {
        cout << "Error: Current room is null!" << endl;
        return;
    }

    // Display room description
    cout << "\n" << here->desc << endl;

    // Show available exits
    cout << "Exits: ";
    bool hasExits = false;
    if (here->northExit != nullptr) { cout << "North "; hasExits = true; }
    if (here->southExit != nullptr) { cout << "South "; hasExits = true; }
    if (here->eastExit != nullptr) { cout << "East "; hasExits = true; }
    if (here->westExit != nullptr) { cout << "West "; hasExits = true; }
    if (!hasExits) cout << "None";
    cout << endl;

    // Show creatures/enemies in the room
    if (!here->mobs.empty()) {
        cout << "Enemies in this room: ";
        for (const auto& creature : here->mobs) {
            cout << creature.getName() << " ";
        }
        cout << endl;
    }

    // Show treasure (only if room is cleared of enemies)
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

/**
 * Adds a creature to the current room
 * Creatures must be defeated before treasure can be collected
 * 
 * @param c Creature object to add to the room
 */
void Map::addCreature(Creature c) {
    here->mobs.push_back(c);
}

/**
 * Retrieves a creature from the current room for combat
 * Removes the creature from the room's mob list (simulating defeat)
 * Uses LIFO (Last In, First Out) order for creature retrieval
 * 
 * @return Creature object for combat, or empty creature if none available
 */
Creature Map::getCreatureForFight() {
    if (!here->mobs.empty()) {
        Creature fighter = here->mobs.back();   // Get last creature in list
        here->mobs.pop_back();                  // Remove from room
        return fighter;
    }
    // Return empty creature if no mobs available
    return Creature("No Enemy", 0);
}

/**
 * Checks if the current room has been cleared of all enemies
 * Used to determine if treasure can be collected and combat is available
 * 
 * @return true if no creatures remain in the room, false otherwise
 */
bool Map::roomCleared() {
    return here->mobs.empty();
}

/**
 * Adds treasure to the current room
 * Treasure can only be collected after all enemies are defeated
 * 
 * @param t Treasure object to add to the room
 */
void Map::addLoot(Treasure t) {
    here->loot.push_back(t);
}

/**
 * Retrieves all treasure from the current room
 * Clears the room's treasure list after retrieval (treasure is taken)
 * Should only be called after verifying the room is cleared of enemies
 * 
 * @return vector containing all Treasure objects from the room
 */
vector<Treasure> Map::getLoot() {
    vector<Treasure> roomLoot = here->loot;     // Copy treasure list
    here->loot.clear();                         // Clear room's treasure
    return roomLoot;
}