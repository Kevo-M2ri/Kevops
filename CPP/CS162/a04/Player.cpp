#include "Player.h"
#include <iostream>
#include <iomanip>
using namespace std;

Player::Player(int hp) : maxHp(hp), currentHp(hp) {}

int Player::getMaxHp() const { return maxHp; }
int Player::getCurrentHp() const { return currentHp; }

void Player::takeDamage(int damage) {
    currentHp -= damage;
    if (currentHp < 0) currentHp = 0;
}

void Player::heal(int amount) {
    currentHp += amount;
    if (currentHp > maxHp) currentHp = maxHp;
}

bool Player::isAlive() const { return currentHp > 0; }

void Player::addMove(const Attack& attack) { moves.push_back(attack); }
vector<Attack> Player::getMoves() const { return moves; }

Attack Player::getMove(int index) const {
    if (index >= 0 && index < static_cast<int>(moves.size())) {
        return moves[index];
    }
    return Attack();
}

void Player::addLoot(const Treasure& treasure) { loot.push_back(treasure); }
vector<Treasure> Player::getLoot() const { return loot; }

int Player::getTotalWorth() const {
    int total = 0;
    for (const auto& treasure : loot) {
        total += treasure.worth;
    }
    return total;
}

void Player::printStats() const {
    cout << "Player Stats:" << endl;
    cout << "HP: " << currentHp << "/" << maxHp << endl;
    cout << "Total Loot Worth: " << getTotalWorth() << " gold" << endl;
}

void Player::printMoves() const {
    cout << "Available Moves:" << endl;
    for (size_t i = 0; i < moves.size(); i++) {
        cout << i+1 << ". " << moves[i].name 
             << " (Damage: " << moves[i].damage 
             << ", Hit%: " << moves[i].hitPercentage << "%)" << endl;
    }
}

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