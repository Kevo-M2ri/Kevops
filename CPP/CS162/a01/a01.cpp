#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

const int MAX_NAME_LEN = 20;
const int MAX_ATTACK_TEXT_LEN = 4;
const int MAX_INVENTORY = 10;
const int MAX_TREASURES = 2; // per creature

struct Treasure {
    char name[MAX_NAME_LEN];
    int value;
};

struct Creature {
    char name[MAX_NAME_LEN];
    int health;
    int attack;
    char attackText[MAX_ATTACK_TEXT_LEN];
    Treasure treasures[MAX_TREASURES];
    int treasureCount;
};

Treasure randomTreasure();
Creature randomCreature();
bool doBattle(Creature &monster, int &playerHP, Treasure inventory[], int &inventoryCount);
void printInventory(Treasure inventory[]);
int main() {
    srand(time(nullptr));

    int playerHP = 50;
    Treasure inventory[MAX_INVENTORY];
    int inventoryCount = 0;

    return 0;
}