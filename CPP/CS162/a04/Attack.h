#ifndef ATTACK_H
#define ATTACK_H

#include <string>
using namespace std;

struct Attack {
    string name;
    int damage;
    int hitPercentage;

    Attack(string n, int d, int h) : name(n), damage(d), hitPercentage(h) {}
    Attack() : name(""), damage(0), hitPercentage(0) {}
};

#endif