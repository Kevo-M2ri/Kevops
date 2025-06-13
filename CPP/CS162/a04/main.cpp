#include "Map.h"
#include "Player.h"
#include "Creature.h"
#include "Attack.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Functions to create different types of monsters
Creature makeGoblin() {
    Creature goblin("Goblin", 30);
    goblin.addMove(Attack("Slash", 8, 80));
    goblin.addMove(Attack("Bite", 5, 90));
    return goblin;
}

Creature makeAngryCompiler() {
    Creature compiler("Angry Compiler", 50);
    compiler.addMove(Attack("Syntax Error", 12, 70));
    compiler.addMove(Attack("Segmentation Fault", 20, 50));
    compiler.addMove(Attack("Memory Leak", 6, 95));
    return compiler;
}

Creature makeOrc() {
    Creature orc("Orc", 40);
    orc.addMove(Attack("Club Smash", 15, 75));
    orc.addMove(Attack("Roar", 3, 100));
    return orc;
}

Creature makeDragon() {
    Creature dragon("Dragon", 100);
    dragon.addMove(Attack("Fire Breath", 25, 80));
    dragon.addMove(Attack("Claw Swipe", 18, 85));
    dragon.addMove(Attack("Tail Whip", 12, 90));
    return dragon;
}

void initMap(Map &m){
  // this is an example of how to handle adding things to the dungeon before you start
  // it won't compile until you add all the necessary bits
  m.addCreature(makeGoblin());
  m.addLoot(Treasure("A golden pencil", 10000));
  m.addEast("A lounge with an ominous aura");
  m.moveEast();
  m.addCreature(makeAngryCompiler());
  m.addLoot(Treasure("A silky chicken", 100000000000));
  m.addNorth("The watercooler of the damned");
  m.moveNorth();
  m.addCreature(makeDragon());
  m.addLoot(Treasure("Dragon's Hoard", 500000));
  m.moveWest(); // need to go back to the start

  // Add more rooms and creatures
  m.addWest("A musty armory");
  m.moveWest();
  m.addCreature(makeOrc());
  m.addLoot(Treasure("Rusty Sword", 500));

  // Go back to start
  m.moveEast();
  m.moveWest(); // back to start
}

// Combat system
bool attemptHit(int hitPercentage) {
    return (rand() % 100) < hitPercentage;
}

void combat(Player& player, Creature& enemy) {
    cout << "\n=== COMBAT BEGINS ===" << endl;
    cout << "You encounter a " << enemy.getName() << "!" << endl;

    while (player.isAlive() && enemy.isAlive()) {
        cout << "\n--- Your Turn ---" << endl;
        player.printStats();
        enemy.printStats();

        cout << "\nChoose your attack:" << endl;
        player.printMoves();

        int choice;
        cin >> choice;
        choice--; // convert to 0-based index

        if (choice >= 0 && choice < player.getMoves().size()) {
            Attack playerAttack = player.getMove(choice);
            cout << "\nYou use " << playerAttack.name << "!" << endl;

            if (attemptHit(playerAttack.hitPercentage)) {
                cout << "Hit! You deal " << playerAttack.damage << " damage!" << endl;
                enemy.takeDamage(playerAttack.damage);
            } else {
                cout << "Miss! Your attack failed!" << endl;
            }
        } else {
            cout << "Invalid choice! You lose your turn!" << endl;
        }

        if (!enemy.isAlive()) {
            cout << "\nYou defeated the " << enemy.getName() << "!" << endl;
            break;
        }

        // Enemy's turn
        cout << "\n--- Enemy Turn ---" << endl;
        Attack enemyAttack = enemy.getRandomMove();
        cout << enemy.getName() << " uses " << enemyAttack.name << "!" << endl;

        if (attemptHit(enemyAttack.hitPercentage)) {
            cout << "The attack hits! You take " << enemyAttack.damage << " damage!" << endl;
            player.takeDamage(enemyAttack.damage);
        } else {
            cout << "The attack misses!" << endl;
        }

        if (!player.isAlive()) {
            cout << "\nYou have been defeated!" << endl;
            break;
        }
    }
}

void showCommands() {
    cout << "\nCommands:" << endl;
    cout << "n/north - Move north" << endl;
    cout << "s/south - Move south" << endl;
    cout << "e/east - Move east" << endl;
    cout << "w/west - Move west" << endl;
    cout << "f/fight - Fight an enemy in the room" << endl;
    cout << "l/loot - Take loot from the room" << endl;
    cout << "stats - Show your stats" << endl;
    cout << "inventory - Show your inventory" << endl;
    cout << "help - Show this help message" << endl;
    cout << "quit - Exit the game" << endl;
}

int main(){
    srand(time(0)); // seed random number generator

    Map m = Map("The dark entryway of the dungeon stretches out before you");

    // Create player
    Player player(100);
    player.addMove(Attack("Sword Strike", 10, 85));
    player.addMove(Attack("Shield Bash", 6, 95));
    player.addMove(Attack("Power Attack", 18, 65));

    initMap(m);

    cout << "Welcome to the Dungeon Explorer!" << endl;
    cout << "Type 'help' for a list of commands." << endl;

    m.printRoom();

    string command;
    while (player.isAlive() && cin >> command) {
        if (command == "quit" || command == "q") {
            break;
        } else if (command == "help" || command == "h") {
            showCommands();
        } else if (command == "north" || command == "n") {
            m.moveNorth();
        } else if (command == "south" || command == "s") {
            m.moveSouth();
        } else if (command == "east" || command == "e") {
            m.moveEast();
        } else if (command == "west" || command == "w") {
            m.moveWest();
        } else if (command == "fight" || command == "f") {
            if (m.roomCleared()) {
                cout << "No enemies to fight in this room!" << endl;
            } else {
                Creature enemy = m.getCreatureForFight();
                combat(player, enemy);
            }
        } else if (command == "loot" || command == "l") {
            if (!m.roomCleared()) {
                cout << "You must defeat all enemies before taking loot!" << endl;
            } else {
                vector<Treasure> roomLoot = m.getLoot();
                if (roomLoot.empty()) {
                    cout << "No loot in this room!" << endl;
                } else {
                    cout << "You collected:" << endl;
                    for (const auto& treasure : roomLoot) {
                        player.addLoot(treasure);
                        cout << "- " << treasure.name << " (Worth: " << treasure.worth << " gold)" << endl;
                    }
                }
            }
        } else if (command == "stats") {
            player.printStats();
        } else if (command == "inventory" || command == "i") {
            player.printLoot();
        } else {
            cout << "Unknown command. Type 'help' for available commands." << endl;
        }

        if (!player.isAlive()) {
            cout << "\nGAME OVER - You have died!" << endl;
            break;
        }
    }

    cout << "\nThanks for playing!" << endl;
    cout << "Final Stats:" << endl;
    player.printStats();

    return 0;
}