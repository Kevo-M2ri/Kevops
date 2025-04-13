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

Creature randomEnemy();
Creature makeSkeleton();
Creature makeGoblin();
Creature makeDragon();
Creature makeBoss();
void displayInventory(Treasure inventory[], int inventoryCount);
int calculateTotalValue(Treasure inventory[], int inventoryCount);
int performAttack(int attackType, Creature &enemy);
void performEnemyAttack(Creature &enemy, int &playerHP);
void addTreasure(Treasure newTreasure, Treasure inventory[], int &inventoryCount);
void displayGameStatus(int playerHP, int enemyHP, Treasure inventory[], int inventoryCount);
void clearScreen();
void pressEnterToContinue();

int main() {
    srand(time(nullptr));

    int playerHP = 50;
    int playerAttack = 10;
    Treasure inventory[MAX_INVENTORY];
    int inventoryCount = 0;
    int choice;
    int attackChoice;

    return 0;
}

Creature randomEnemy() {
    int enemyType = rand() % 4;
    switch (enemyType) {
        case 0:
            return makeSkeleton();
        case 1:
            return makeGoblin();
        case 2:
            return makeDragon();
        default:
            return makeBoss();
    }
}

Creature randomCreature() {
    Creature c;
    c.name = "Creature";
    c.health = rand() % 100 + 1;
    c.attack = rand() % 10 + 1;
    return c;
}

bool doBattle(Creature &monster, int &playerHP, Treasure inventory[], int &inventoryCount) {
    while (playerHP > 0 && monster.health > 0) {
        playerHP -= monster.attack;
        monster.health -= playerHP;
    }
}

void printInventory(Treasure inventory[], int inventoryCount) {
    for (int i = 0; i < inventoryCount; i++) {
        cout << inventory[i].name << " " << inventory[i].value << endl;
    }
}