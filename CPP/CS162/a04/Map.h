#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Creature.h"
#include "Treasure.h"
#include <string>

using namespace std;

/**
 * Map class - manages the dungeon layout and room system
 * Creates a connected network of rooms that the player can navigate
 * Each room can contain enemies, treasures, and exits to other rooms
 */
class Map {
private:
    /**
     * Room structure - represents a single location in the dungeon
     * Contains description, contents, and pointers to adjacent rooms
     */
    struct room {
        string desc;                // Description of the room
        vector<Creature> mobs;      // Enemies present in this room
        vector<Treasure> loot;      // Treasures available in this room
        room* eastExit;             // Pointer to room to the east (null if no exit)
        room* westExit;             // Pointer to room to the west (null if no exit)
        room* northExit;            // Pointer to room to the north (null if no exit)
        room* southExit;            // Pointer to room to the south (null if no exit)
    };

    // Helper function for destructor - recursively deletes all connected rooms
    void deleteRoom(room* r, vector<room*>& visited);
    
    room* here;                     // Pointer to current room where player is located

public: 
    // Constructor - creates starting room with given description
    Map(string description);
    
    // Destructor - cleans up all allocated room memory
    ~Map();

    // Movement methods - attempt to move player in specified direction
    void moveEast();
    void moveWest();
    void moveNorth();
    void moveSouth();

    // Room creation methods - add new rooms adjacent to current location
    void addEast(string description);      // Creates new room to the east
    void addWest(string description);      // Creates new room to the west
    void addNorth(string description);     // Creates new room to the north
    void addSouth(string description);     // Creates new room to the south

    // Room interaction methods
    void printRoom();                      // Displays current room info (description, exits, contents)
    void addCreature(Creature c);          // Adds enemy to current room
    Creature getCreatureForFight();        // Removes and returns enemy for combat
    bool roomCleared();                    // Returns true if no enemies remain in current room

    // Loot management methods
    void addLoot(Treasure t);              // Adds treasure to current room
    vector<Treasure> getLoot();            // Removes and returns all treasures from current room
};

#endif