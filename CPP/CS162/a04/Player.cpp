#include "Player.h"
#include <iostream>
#include <iomanip>
using namespace std;

/**
 * Constructor - initializes player with specified HP
 * Sets both current and maximum HP to the same value
 */
Player::Player(int hp) : maxHp(hp), currentHp(hp) {}

// Health getter methods
int Player::getMaxHp() const { return maxHp; }
int Player::getCurrentHp() const { return currentHp; }

/**
 * Reduces player's current HP by damage amount
 * Prevents HP from going below 0
 */
void Player::takeDamage(int damage) {
    currentHp -= damage;
    if (currentHp < 0) currentHp = 0;  // Prevent negative HP
}

/**
 * Restores player's HP by specified amount
 * Prevents HP from exceeding maximum
 */
void Player::heal(int amount) {
    currentHp += amount;
    if (currentHp > maxHp) currentHp = maxHp;  // Cap at maximum HP
}

/**
 * Checks if player is still alive (current HP > 0)
 */
bool Player::isAlive() const { 
    return currentHp > 0; 
}

/**
 * Adds a new attack to the player's available moves
 */
void Player::addMove(const Attack& attack) { 
    moves.push_back(attack); 
}

/**
 * Returns all attacks available to the player
 */
vector<Attack> Player::getMoves() const { 
    return moves; 
}

/**
 * Returns a specific attack by index
 * Returns empty attack if index is out of bounds
 */
Attack Player::getMove(int index) const {
    if (index >= 0 && index < static_cast<int>(moves.size())) {
        return moves[index];
    }
    return Attack();  // Return empty attack if invalid index
}

/**
 * Adds treasure to the player's inventory
 */
void Player::addLoot(const Treasure& treasure) { 
    loot.push_back(treasure); 
}

/**
 * Returns all treasures in the player's inventory
 */
vector<Treasure> Player::getLoot() const { 
    return loot; 
}

/**
 * Calculates and returns the total gold value of all collected treasures
 */
int Player::getTotalWorth() const {
    int total = 0;
    for (const auto& treasure : loot) {
        total += treasure.worth;
    }
    return total;
}

/**
 * Displays the player's current stats (HP and total loot value)
 */
void Player::printStats() const {
    cout << "Player Stats:" << endl;
    cout << "HP: " << currentHp << "/" << maxHp << endl;
    cout << "Total Loot Worth: " << getTotalWorth() << " gold" << endl;
}

/**
 * Displays all available combat moves with their damage and hit chance
 */
void Player::printMoves() const {
    cout << "Available Moves:" << endl;
    for (size_t i = 0; i < moves.size(); i++) {
        cout << i+1 << ". " << moves[i].name 
             << " (Damage: " << moves[i].damage 
             << ", Hit%: " << moves[i].hitPercentage << "%)" << endl;
    }
}

/**
 * Displays the player's complete treasure inventory
 * Shows each item's name and individual worth
 */
void Player::printLoot() const {
    if (loot.empty()) {
        cout << "No loot collected yet." << endl;
        return;
    }
    
    cout << "Collected Loot:" << endl;
    for (const auto& treasure : loot) {
        cout << "- " << treasure.name << " (Worth: " << treasure.worth << " gold)" << endl;
    }
}