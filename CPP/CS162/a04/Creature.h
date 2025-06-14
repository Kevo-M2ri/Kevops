#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <string>
#include "Attack.h"
using namespace std;

class Creature {
private:
    string name;
    int hp;
    vector<Attack> moves;

public:
    Creature(string n, int health);

    string getName() const;
    int getHp() const;
    bool isAlive() const;

    void takeDamage(int damage);
    void addMove(const Attack& attack);
    vector<Attack> getMoves() const;
    Attack getRandomMove() const;

    void printStats() const;
};

#endif