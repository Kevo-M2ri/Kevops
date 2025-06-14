#ifndef TREASURE_H
#define TREASURE_H

#include <string>
using namespace std;

/**
 * Treasure structure - represents valuable items that can be found
 * and collected by the player throughout the dungeon
 */
struct Treasure {
    string name;    // Display name of the treasure item
    int worth;      // Gold value of the treasure

    // Constructor with parameters
    Treasure(string n, int w) : name(n), worth(w) {}
    
    // Default constructor - creates an empty/valueless treasure
    Treasure() : name(""), worth(0) {}
};

#endif