#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Attack.h"
#include "Treasure.h"
using namespace std;

class Player {
private:
    int maxHp;
    int currentHp;
    vector<Attack> moves;
    vector<Treasure> loot;

public:
    Player(int hp);

    // Health management
    int getMaxHp() const;
    int getCurrentHp() const;
    void takeDamage(int damage);
    void heal(int amount);
    bool isAlive() const;

    // Move management
    void addMove(const Attack& attack);
    vector<Attack> getMoves() const;
    Attack getMove(int index) const;

    // Loot management
    void addLoot(const Treasure& treasure);
    vector<Treasure> getLoot() const;
    int getTotalWorth() const;

    // Display functions
    void printStats() const;
    void printMoves() const;
    void printLoot() const;
};

#endif