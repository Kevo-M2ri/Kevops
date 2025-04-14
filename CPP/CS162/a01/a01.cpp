/*---------------------------------------------------------------------------
    Author: Kelvin Muturi
    Date: 2025-04-13
    This is a simple text-based RPG game where the player can
    fight random enemies, check their inventory, and run away.
    The player can collect treasures from defeated enemies.
    This code has been written in C++, using visual studio code as the IDE.
    It was tested on a Windows 11 machine.
---------------------------------------------------------------------------*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
using namespace std;

// Constants definition
const int MAX_NAME_LEN = 20;
const int MAX_ATTACK_TEXT_LEN = 50;
const int MAX_INVENTORY = 10;
const int MAX_TREASURES = 2;

// Treasure structure definition
struct Treasure {
    char name[MAX_NAME_LEN];
    int value;
};

// Creature structure definition
struct Creature {
    char enemyName[MAX_NAME_LEN];
    int health;
    int attack;
    int attackPercent;
    char attackText[MAX_ATTACK_TEXT_LEN];
    Treasure treasures[MAX_TREASURES]; 
    int treasureCount;
};

// Function prototypes
Creature randomEnemy();
Creature makeSkeleton();
Creature makeGoblin();
Creature makeDragon();
Creature makeWolf();
Creature makeVampire();
void displayInventory(Treasure inventory[], int inventoryCount);
int calculateTotalValue(Treasure inventory[], int inventoryCount);
int performAttack(int attackType, Creature &enemy);
void performEnemyAttack(Creature enemy, int &playerHP);
void addTreasure(Creature enemy, Treasure inventory[], int &inventoryCount);
void displayGameStatus(int playerHP, int enemyHP, const char* enemyName);

// Main function
int main() {
    srand(time(nullptr)); // Seed the random number generator

    // Game variables
    int playerHP = 50; // Player's initial health
    Treasure inventory[MAX_INVENTORY]; // Player's inventory
    int inventoryCount = 0; // Number of items in inventory
    int choice; // User's menu choice
    int attackChoice; // User's attack choice

    while (playerHP > 0) {
        // Display main menu
        cout << "--- Main Menu ---" << endl;
        cout << "1) Fight" << endl;
        cout << "2) Check Inventory" << endl;
        cout << "3) Run" << endl;
        cout << "Choose an option: ";
        cin >> choice;
        cin.ignore(10000, '\n');
        cout << endl;

        switch (choice) {
            case 1: {
                Creature enemy = randomEnemy(); // Generate a random enemy
                
                cout << "A wild " << enemy.enemyName << " appears! It has " << enemy.health << " HP." << endl;

                while (enemy.health > 0 && playerHP > 0) { // Battle loop
                    displayGameStatus(playerHP, enemy.health, enemy.enemyName); // Display game status function call
                    
                    cout << "Choose your attack:" << endl;
                    cout << "1) Quick Strike (70% chance, 4 damage)" << endl;
                    cout << "2) Heavy Blow (50% chance, 8 damage)" << endl;
                    cout << "Enter choice: "; // User's attack choice

                    cin >> attackChoice; // User input for attack choice
                    cin.ignore(10000, '\n'); // Clear the input buffer

                    if (performAttack(attackChoice, enemy)) { // Perform attack function call
                        cout << "You defeated the " << enemy.enemyName << "!" << endl << endl;
                        addTreasure(enemy, inventory, inventoryCount); // Add treasure to inventory function call
                        break;
                    } // Enemy attack phase

                    if (enemy.health > 0) {
                        performEnemyAttack(enemy, playerHP); // Perform enemy attack function call till health is 0
                    }
                } // End of battle loop
                break;
            } // fight case

            case 2: {
                cout << "--- Your Inventory ---" << endl;
                displayInventory(inventory, inventoryCount); // Display inventory function call
                cout << endl;
                break;
            }// check inventory case
            case 3: {
                cout << "You chose to run away." << endl;
                cout << "You collected a total of " << calculateTotalValue(inventory, inventoryCount) << " gil." << endl; //show total gil
                return 0;
            } // run case
        } // End of switch case

        if (playerHP <= 0) {
            cout << "You have been defeated by the " << "monster" << "!" << endl;
            cout << "You collected a total of " << calculateTotalValue(inventory, inventoryCount) << " gil." << endl; //show total gil
            return 0;
        } // End of player defeat check
    }

    return 0;
}// End of main function

// Function implementations
Creature randomEnemy() {
    int enemyType = rand() % 5; // Randomly select an enemy type
    switch (enemyType) { // enemy type switch case
        case 0: return makeSkeleton();
        case 1: return makeGoblin();
        case 2: return makeDragon();
        case 3: return makeWolf();
        case 4: return makeVampire();
        default: return makeSkeleton();
    }
}// End of randomEnemy function

// Function implementation for skeleton
Creature makeSkeleton() {
    Creature skeleton; //variable for skeleton
    strcpy(skeleton.enemyName, "Skeleton"); //copy skeleton as enemy name
    skeleton.health = 20 + (rand() % 10); // random health for skeleton
    skeleton.attack = 5 + (rand() % 3); // random attack for skeleton
    skeleton.attackPercent = 80; // random attack percent for skeleton
    strcpy(skeleton.attackText, "The skeleton attacks with its bony hands!");

    skeleton.treasureCount = 1 + (rand() % MAX_TREASURES); // random treasure count for skeleton
    for (int i = 0; i < skeleton.treasureCount; i++) {
        if (i == 0) {
            strcpy(skeleton.treasures[i].name, "Skull"); // copy skull as treasure name
            skeleton.treasures[i].value = 5 + (rand() % 10);
        } // condition for skeleton treasure 
        else {
            strcpy(skeleton.treasures[i].name, "Finger Bones"); // copy finger bones as treasure name
            skeleton.treasures[i].value = 5 + (rand() % 5);
        } // condition for skeleton treasure
    } // end of for loop
    return skeleton;
}// End of makeSkeleton function

// Function implementation for goblin
Creature makeGoblin() {
    Creature goblin;
    strcpy(goblin.enemyName, "Goblin"); // copy goblin as enemy name
    goblin.health = 15 + (rand() % 10); // random health for goblin
    goblin.attack = 4 + (rand() % 3); // random attack for goblin
    goblin.attackPercent = 75;  // random attack percent for goblin
    strcpy(goblin.attackText, "The goblin swings a spiked club at you!");

    goblin.treasureCount = 1 + (rand() % MAX_TREASURES); // random treasure count for goblin
    for (int i = 0; i < goblin.treasureCount; i++) {
        if (i == 0) {
            strcpy(goblin.treasures[i].name, "Gold Coin");
            goblin.treasures[i].value = 10;
        } // condition for goblin treasure
        else {
            strcpy(goblin.treasures[i].name, "Gold Coin");
            goblin.treasures[i].value = 10;
        } // condition for goblin treasure
    } // end of for loop
    return goblin;
}// End of makeGoblin function

// Function implementation for dragon
Creature makeDragon() {
    Creature dragon; //variable for dragon
    strcpy(dragon.enemyName, "Dragon");// copy dragon as enemy name
    dragon.health = 30 + (rand() % 20); // random health for dragon
    dragon.attack = 10 + (rand() % 5); // random attack for dragon
    dragon.attackPercent = 60; // random attack percent for dragon
    strcpy(dragon.attackText, "The dragon breathes fire at you!");

    dragon.treasureCount = 1 + (rand() % MAX_TREASURES); // random treasure count for dragon
    for (int i = 0; i < dragon.treasureCount; i++) {
        int treasureType = rand() % 3;
        if (treasureType == 0) {
            strcpy(dragon.treasures[i].name, "Dragon Scale");
            dragon.treasures[i].value = 15 + (rand() % 20);
        }// condition for dragon treasure
        else if (treasureType == 1) {
            strcpy(dragon.treasures[i].name, "Gold Nugget");
            dragon.treasures[i].value = 20 + (rand() % 30);
        // condition for dragon treasure
        } 
        else {
            strcpy(dragon.treasures[i].name, "Ruby");
            dragon.treasures[i].value = 10 + (rand() % 15);
        }// condition for dragon treasure
    } // end of for loop
    return dragon;
} // End of makeDragon function

// Function implementation for wolf
Creature makeWolf() {
    Creature wolf; //variable for wolf
    strcpy(wolf.enemyName, "WereWolf"); // copy werewolf as enemy name
    wolf.health = 25 + (rand() % 15); // random health for wolf
    wolf.attack = 8 + (rand() % 4); // random attack for wolf
    wolf.attackPercent = 70; // random attack percent for wolf
    strcpy(wolf.attackText, "The werewolf slashes at you with its claws!");

    wolf.treasureCount = 1 + (rand() % MAX_TREASURES); // random treasure count for wolf
    for (int i = 0; i < wolf.treasureCount; i++) {
        if (i == 0) {
            strcpy(wolf.treasures[i].name, "Wolf Fang");
            wolf.treasures[i].value = 5 + (rand() % 10);
        }// condition for wolf treasure
        else {
            strcpy(wolf.treasures[i].name, "Silver Claw");
            wolf.treasures[i].value = 10 + (rand() % 15);
        } // condition for wolf treasure
    }// end of for loop
    return wolf;
} // End of makeWolf function

// Function implementation for vampire
Creature makeVampire() {
    Creature vampire;
    strcpy(vampire.enemyName, "Dracula");
    vampire.health = 20 + (rand() % 15);
    vampire.attack = 7 + (rand() % 5);
    vampire.attackPercent = 65;
    strcpy(vampire.attackText, "The vampire lunges at you with its fangs!");

    vampire.treasureCount = 1 + (rand() % MAX_TREASURES);
    for (int i = 0; i < vampire.treasureCount; i++) {
        if (i == 0) {
            strcpy(vampire.treasures[i].name, "Vampire Fang");
            vampire.treasures[i].value = 10 + (rand() % 15);
        }
        else {
            strcpy(vampire.treasures[i].name, "Blood Ruby");
            vampire.treasures[i].value = 15 + (rand() % 25);
        }
    }
    return vampire;
} // End of makeVampire function

// Function implementations for inventory management
void displayInventory(Treasure inventory[], int inventoryCount) {
    if (inventoryCount == 0) { // check if inventory is empty
        cout << "It's empty! No items yet." << endl;
        return;
    }
    
    for (int i = 0; i < inventoryCount; i++) { // loop through inventory
        cout << i + 1 << ") " << inventory[i].name << " (Value: " << inventory[i].value << " gil)" << endl;
    }
    cout << "Total worth: " << calculateTotalValue(inventory, inventoryCount) << " gil" << endl;
} // End of displayInventory function

// Function to calculate total value of inventory
int calculateTotalValue(Treasure inventory[], int inventoryCount) {
    int totalValue = 0;
    for (int i = 0; i < inventoryCount; i++) {
        totalValue += inventory[i].value; // accumulate total value of inventory
    }
    return totalValue;
}// End of calculateTotalValue function

// Function to perform player's attack
int performAttack(int attackType, Creature &enemy) {
    int hitChance = rand() % 100; // Random hit chance
    bool hit = false; // hit status
    int damage = 0; // damage dealt

    switch (attackType) {
        case 1: // Quick Strike
            if (hitChance < 70) {
                hit = true; // successful hit
                damage = 4; // damage dealt
                cout << "You struck the " << enemy.enemyName << " for " << damage << " damage!" << endl; // successful attack message
            }
            else {
                cout << "Your attack missed!" << endl; // missed attack message
            }
            break;
        case 2: // Heavy Blow
            if (hitChance < 50) {
                hit = true; // successful hit
                damage = 8; // damage dealt
                cout << "You struck the " << enemy.enemyName << " for " << damage << " damage!" << endl; // successful attack message
            }
            else {
                cout << "Your attack missed!" << endl;
            }
            break;
        default:
            cout << "Invalid attack choice!" << endl;
            return 0;
    }// end of switch case

    if (hit) {
        enemy.health -= damage; // reduce enemy health
        if (enemy.health <= 0) {
            enemy.health = 0;
            return 1; // Enemy defeated
        }
    }
    return 0; // Enemy not defeated
} // End of performAttack function

// Function to perform enemy's attack
void performEnemyAttack(Creature enemy, int &playerHP) {
    int attackRoll = rand() % 100; // Random attack roll

    cout << enemy.attackText << endl; // enemy attack message

    if (attackRoll < enemy.attackPercent) {
        playerHP -= enemy.attack; // reduce player health
        if (playerHP < 0) playerHP = 0; // prevent negative health
        cout << "The " << enemy.enemyName << " hit you for " << enemy.attack << " damage!" << endl;
    }
    else {
        cout << "The " << enemy.enemyName << " missed!" << endl; // missed enemy attack message
    } // end of if-else statement
} // End of performEnemyAttack function

// Function to add treasure to inventory
void addTreasure(Creature enemy, Treasure inventory[], int &inventoryCount) {
    for (int i = 0; i < enemy.treasureCount; i++) {
        if (inventoryCount < MAX_INVENTORY) {
            inventory[inventoryCount] = enemy.treasures[i]; // add treasure to inventory
            inventoryCount++; // increment inventory count
        } // end of if statement
    } // end of for loop
} // End of addTreasure function

// Function to display game status
void displayGameStatus(int playerHP, int enemyHP, const char* enemyName) {
    cout << "[Your HP: " << playerHP << "] [" << enemyName << " HP: " << enemyHP << "]" << endl; // display game status
}// End of displayGameStatus function