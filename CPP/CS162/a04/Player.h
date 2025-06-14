#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Attack.h"
#include "Treasure.h"
using namespace std;

/**
 * Player class - represents the player character in the dungeon game
 * Manages health, combat moves, and collected treasure inventory
 */
class Player {
private:
    int maxHp;                      // Maximum hit points (for healing reference)
    int currentHp;                  // Current hit points
    vector<Attack> moves;           // Available combat moves
    vector<Treasure> loot;          // Collected treasure items

public:
    // Constructor - creates player with specified starting HP
    Player(int hp);

    // Health management methods
    int getMaxHp() const;           // Returns maximum HP
    int getCurrentHp() const;       // Returns current HP
    void takeDamage(int damage);    // Reduces current HP by damage amount
    void heal(int amount);          // Restores HP (up to maximum)
    bool isAlive() const;           // Returns true if current HP > 0

    // Combat move management
    void addMove(const Attack& attack);     // Adds new attack to player's arsenal
    vector<Attack> getMoves() const;        // Returns all available attacks
    Attack getMove(int index) const;        // Returns specific attack by index

    // Treasure/loot management
    void addLoot(const Treasure& treasure); // Adds treasure to inventory
    vector<Treasure> getLoot() const;       // Returns all collected treasures
    int getTotalWorth() const;              // Calculates total value of all loot

    // Display/UI methods
    void printStats() const;                // Shows current HP and total loot value
    void printMoves() const;                // Lists all available attacks with stats
    void printLoot() const;                 // Shows detailed inventory
};

#endif