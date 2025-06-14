#ifndef ATTACK_H
#define ATTACK_H

#include <string>
using namespace std;

/**
 * Attack structure - represents a combat move that can be performed
 * by either the player or creatures in the game
 */
struct Attack {
    string name;         // Display name of the attack
    int damage;          // Amount of damage the attack deals
    int hitPercentage;   // Probability (0-100) that the attack will hit

    // Constructor with parameters
    Attack(string n, int d, int h) : name(n), damage(d), hitPercentage(h) {}
    
    // Default constructor - creates an empty/invalid attack
    Attack() : name(""), damage(0), hitPercentage(0) {}
};

#endif