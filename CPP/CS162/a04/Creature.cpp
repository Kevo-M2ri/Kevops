#include "Creature.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;

Creature::Creature(string n, int health) : name(n), hp(health) {}

string Creature::getName() const {
    return name;
}

int Creature::getHp() const {
    return hp;
}

bool Creature::isAlive() const {
    return hp > 0;
}

void Creature::takeDamage(int damage) {
    hp -= damage;
    if (hp < 0) hp = 0;
}

void Creature::addMove(const Attack& attack) {
    moves.push_back(attack);
}

vector<Attack> Creature::getMoves() const {
    return moves;
}

Attack Creature::getRandomMove() const {
    if (moves.empty()) {
        return Attack();
    }
    int randomIndex = rand() % moves.size();
    return moves[randomIndex];
}

void Creature::printStats() const {
    cout << name << " HP: " << hp << endl;
}