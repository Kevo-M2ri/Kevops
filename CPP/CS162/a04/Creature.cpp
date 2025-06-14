#include "Creature.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

/**
 * Constructor - initializes a creature with name and health
 */
Creature::Creature(string n, int health) : name(n), hp(health) {}

/**
 * Returns the creature's name
 */
string Creature::getName() const {
    return name;
}

/**
 * Returns the creature's current hit points
 */
int Creature::getHp() const {
    return hp;
}

/**
 * Checks if the creature is still alive (has HP > 0)
 */
bool Creature::isAlive() const {
    return hp > 0;
}

/**
 * Reduces the creature's HP by the specified damage amount
 * Ensures HP doesn't go below 0
 */
void Creature::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;  // Prevent negative HP
}

/**
 * Adds a new attack to the creature's available moves
 */
void Creature::addMove(const Attack& attack) {
    moves.push_back(attack);
}

/**
 * Returns all attacks available to this creature
 */
vector<Attack> Creature::getMoves() const {
    return moves;
}

/**
 * Selects and returns a random attack from the creature's moveset
 * Used by AI to choose attacks during combat
 */
Attack Creature::getRandomMove() const {
    // Return empty attack if no moves available
    if (moves.empty()) {
        return Attack();
    }
    
    // Select random move from available attacks
    int randomIndex = rand() % moves.size();
    return moves[randomIndex];
}

/**
 * Displays the creature's current status (name and HP)
 */
void Creature::printStats() const {
    cout << name << " HP: " << hp << endl;
}
