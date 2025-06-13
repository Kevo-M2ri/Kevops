#ifndef POKEMON_H
#define POKEMON_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

struct Pokemon {
    string name;
    string type1, type2;   // type2 is "" if mono‑type
    int hp, attack, defense,
        special_attack, special_defense, speed,
        total;                  // convenience field

  bool isWeakTo(string aType);
  bool isStrongTo(string aType);
};

bool isWeak(string aType, string dType);
bool isStrong(string aType, string dType);

#endif