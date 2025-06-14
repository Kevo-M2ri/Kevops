#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <string>
#include "Attack.h"
using namespace std;

/**
 * Creature class - represents enemies that the player can encounter
 * and fight in the dungeon. Each creature has health, attacks, and a name.
 */
class Creature {
private:
    string name;            // Name of the creature (e.g., "Goblin", "Dragon")
    int hp;                 // Current hit points/health
    vector<Attack> moves;   // List of attacks this creature can perform

public:
    // Constructor - creates a creature with a name and starting health
    Creature(string n, int health);

    // Getter methods
    string getName() const;     // Returns the creature's name
    int getHp() const;         // Returns current hit points
    bool isAlive() const;      // Returns true if creature has HP > 0

    // Combat methods
    void takeDamage(int damage);              // Reduces HP by damage amount
    void addMove(const Attack& attack);       // Adds an attack to the creature's moveset
    vector<Attack> getMoves() const;          // Returns all available attacks
    Attack getRandomMove() const;             // Selects a random attack for AI use

    // Display methods
    void printStats() const;                  // Prints creature name and current HP
};

#endif