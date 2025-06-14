#include "Map.h"
#include "Player.h"
#include "Creature.h"
#include "Attack.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

/**
 * Monster Creation Functions
 * These functions create different types of creatures with unique stats and movesets
 */

/**
 * Creates a basic Goblin enemy
 * @return Creature object representing a Goblin with low HP and basic attacks
 */
Creature makeGoblin() {
    Creature goblin("Goblin", 30);
    goblin.addMove(Attack("Slash", 8, 80));    // Medium damage, good accuracy
    goblin.addMove(Attack("Bite", 5, 90));     // Low damage, high accuracy
    return goblin;
}

/**
 * Creates an Angry Compiler enemy (programming-themed humor)
 * @return Creature object with programming-related attacks
 */
Creature makeAngryCompiler() {
    Creature compiler("Angry Compiler", 50);
    compiler.addMove(Attack("Syntax Error", 12, 70));         // High damage, medium accuracy
    compiler.addMove(Attack("Segmentation Fault", 20, 50));   // Very high damage, low accuracy
    compiler.addMove(Attack("Memory Leak", 6, 95));           // Low damage, very high accuracy
    return compiler;
}

/**
 * Creates an Orc enemy
 * @return Creature object representing an Orc with moderate stats
 */
Creature makeOrc() {
    Creature orc("Orc", 40);
    orc.addMove(Attack("Club Smash", 15, 75));  // High damage, good accuracy
    orc.addMove(Attack("Roar", 3, 100));        // Low damage, guaranteed hit (intimidation)
    return orc;
}

/**
 * Creates a Dragon boss enemy
 * @return Creature object representing the strongest enemy with multiple powerful attacks
 */
Creature makeDragon() {
    Creature dragon("Dragon", 100);
    dragon.addMove(Attack("Fire Breath", 25, 80));  // Highest damage, good accuracy
    dragon.addMove(Attack("Claw Swipe", 18, 85));   // High damage, good accuracy
    dragon.addMove(Attack("Tail Whip", 12, 90));    // Medium damage, high accuracy
    return dragon;
}

/**
 * Initializes the game map with rooms, creatures, and treasure
 * Creates a small dungeon with 4 interconnected rooms:
 * - Starting room (west) with Goblin
 * - East lounge with Angry Compiler
 * - North watercooler area with Dragon (boss)
 * - West armory with Orc
 * 
 * @param m Reference to the Map object to initialize
 */
void initMap(Map &m) {
    // Starting room setup
    m.addCreature(makeGoblin());
    m.addLoot(Treasure("A golden pencil", 10000));
    
    // Create and move to east room (lounge)
    m.addEast("A lounge with an ominous aura");
    m.moveEast();
    m.addCreature(makeAngryCompiler());
    m.addLoot(Treasure("A silky chicken", 1000000));  // High-value treasure
    
    // Create and move to north room (boss room)
    m.addNorth("The watercooler of the damned");
    m.moveNorth();
    m.addCreature(makeDragon());  // Boss enemy
    m.addLoot(Treasure("Dragon's Hoard", 500000));
    
    // Return to starting position
    m.moveSouth(); // Back to lounge
    m.moveWest();  // Back to start

    // Create west room (armory)
    m.addWest("A musty armory");
    m.moveWest();
    m.addCreature(makeOrc());
    m.addLoot(Treasure("Rusty Sword", 500));
    m.moveEast(); // Return to starting room
}

/**
 * Determines if an attack hits based on hit percentage
 * @param hitPercentage The percentage chance (0-100) for the attack to hit
 * @return true if attack hits, false if it misses
 */
bool attemptHit(int hitPercentage) {
    return (rand() % 100) < hitPercentage;
}

/**
 * Handles turn-based combat between player and enemy
 * Combat continues until either the player or enemy is defeated
 * Player chooses attacks, enemy attacks are chosen randomly
 * 
 * @param player Reference to the Player object
 * @param enemy Reference to the Creature (enemy) object
 */
void combat(Player& player, Creature& enemy) {
    cout << "\n=== COMBAT BEGINS ===" << endl;
    cout << "You encounter a " << enemy.getName() << "!" << endl;

    // Combat loop - continues until one combatant is defeated
    while (player.isAlive() && enemy.isAlive()) {
        // Player's turn
        cout << "\n--- Your Turn ---" << endl;
        player.printStats();
        enemy.printStats();

        // Display attack options and get player choice
        cout << "\nChoose your attack:" << endl;
        player.printMoves();

        int choice;
        // Input validation loop - ensures valid attack selection
        while (!(cin >> choice) || choice < 1 || choice > static_cast<int>(player.getMoves().size())) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input! Please enter a number between 1 and " 
                 << player.getMoves().size() << ": ";
        }
        choice--; // Convert to 0-based index

        // Execute player's attack
        Attack playerAttack = player.getMove(choice);
        cout << "\nYou use " << playerAttack.name << "!" << endl;

        if (attemptHit(playerAttack.hitPercentage)) {
            cout << "Hit! You deal " << playerAttack.damage << " damage!" << endl;
            enemy.takeDamage(playerAttack.damage);
        } else {
            cout << "Miss! Your attack failed!" << endl;
        }

        // Check if enemy is defeated
        if (!enemy.isAlive()) {
            cout << "\nYou defeated the " << enemy.getName() << "!" << endl;
            break;
        }

        // Enemy's turn
        cout << "\n--- Enemy Turn ---" << endl;
        Attack enemyAttack = enemy.getRandomMove();  // AI chooses random attack
        cout << enemy.getName() << " uses " << enemyAttack.name << "!" << endl;

        if (attemptHit(enemyAttack.hitPercentage)) {
            cout << "The attack hits! You take " << enemyAttack.damage << " damage!" << endl;
            player.takeDamage(enemyAttack.damage);
        } else {
            cout << "The attack misses!" << endl;
        }

        // Check if player is defeated
        if (!player.isAlive()) {
            cout << "\nYou have been defeated!" << endl;
            break;
        }
    }
}

/**
 * Displays available game commands to the player
 */
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

/**
 * Main game function - initializes game world and runs main game loop
 * Handles player input and coordinates all game systems
 */
int main() {
    // Initialize random number generator for combat calculations
    srand(static_cast<unsigned int>(time(0)));

    // Initialize game world
    Map m("The dark entryway of the dungeon stretches out before you");
    initMap(m);

    // Create player character with starting stats and attacks
    Player player(100);  // 100 HP
    player.addMove(Attack("Sword Strike", 10, 85));   // Balanced attack
    player.addMove(Attack("Shield Bash", 6, 95));     // Low damage, high accuracy
    player.addMove(Attack("Power Attack", 18, 65));   // High damage, lower accuracy

    // Welcome message and initial room description
    cout << "Welcome to the Dungeon Explorer!" << endl;
    cout << "Type 'help' for a list of commands." << endl;
    m.printRoom();

    // Main game loop - continues until player dies or quits
    string command;
    while (player.isAlive()) {
        cout << "\n> ";
        cin >> command;

        // Command processing - handles all player input
        if (command == "quit" || command == "q") {
            break;
        } else if (command == "help" || command == "h") {
            showCommands();
        } 
        // Movement commands
        else if (command == "north" || command == "n") {
            m.moveNorth();
        } else if (command == "south" || command == "s") {
            m.moveSouth();
        } else if (command == "east" || command == "e") {
            m.moveEast();
        } else if (command == "west" || command == "w") {
            m.moveWest();
        } 
        // Combat command
        else if (command == "fight" || command == "f") {
            if (m.roomCleared()) {
                cout << "No enemies to fight in this room!" << endl;
            } else {
                Creature enemy = m.getCreatureForFight();  // Get next enemy from room
                combat(player, enemy);
            }
        } 
        // Looting command
        else if (command == "loot" || command == "l") {
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
        } 
        // Information commands
        else if (command == "stats") {
            player.printStats();
        } else if (command == "inventory" || command == "i") {
            player.printLoot();
        } 
        // Invalid command handling
        else {
            cout << "Unknown command. Type 'help' for available commands." << endl;
        }
    }

    // Game over sequence
    cout << "\nThanks for playing!" << endl;
    cout << "Final Stats:" << endl;
    player.printStats();

    return 0;
}