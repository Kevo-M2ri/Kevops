#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Creature.h"
#include "Treasure.h"
#include <string>

using namespace std;

class Map {
private:
    struct room {
        string desc;
        vector<Creature> mobs;
        vector<Treasure> loot;
        room* eastExit;
        room* westExit;
        room* northExit;
        room* southExit;
    };

    void deleteRoom(room* r, vector<room*>& visited); // helper function for destructor
    room* here;

public: 
    Map(string description);
    ~Map();

    void moveEast();
    void moveWest();
    void moveNorth();
    void moveSouth();

    void addEast(string description);
    void addWest(string description);
    void addNorth(string description);
    void addSouth(string description);

    void printRoom();
    void addCreature(Creature c);
    Creature getCreatureForFight();
    bool roomCleared();

    void addLoot(Treasure t);
    vector<Treasure> getLoot();
};

#endif