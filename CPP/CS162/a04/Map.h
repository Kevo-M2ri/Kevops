#ifndef MAP_H
#define MAP_H

#include <vector>
#include "Creature.h"
#include "Treasure.h"
#include <string>

using namespace std;

class Map{

 public: 
  Map(string description); // this makes a first room with new and sets its description
  ~Map(); // this is going to involve four way recursion down all the possible exits
  // I've actually written this for you because there's a really neat trick
  // that's worth explaining

  void moveEast(); // this print "you can't go that way" if there's no room in that direction
  void moveWest();
  void moveNorth();
  void moveSouth();

  // For all of these functions make sure that for the newly created room you set the "back link" immediately
  // So addEast, for example, should make a room
  // set its west pointer to the current room
  // then set the current room's eastExit pointer to the newly created room
  void addEast(string description); // make a new room, sets its description, add it to the east pointer
  void addWest(string description); // the same for the other directions
  void addNorth(string description);
  void addSouth(string description);
  
  void printRoom(); // this is the function that should show the room to the player
  // only print valid i.e. non nullptr exits!

  void addCreature(Creature c);
  Creature getCreatureForFight(); // this pops a creature out in order to initiate the fight
  bool roomCleared(); // returns true if there are no enemies left in the room, use this to tell if you can take the loot
  
  void addLoot(Treasure t); //adds loot to a room
  vector<Treasure> getLoot(); // should return the loot from the room and remove it from the room itself
  
  
 private:
  void deleteRoom(room* r, vector<room*>& visited); // helper function for destructor
  struct room {
    string desc; // This is what prints as the description of the room
    vector <Creature> mobs; 
    vector<Treasure> loot;
    room* eastExit;
    room* westExit;
    room* northExit;
    room* southExit;
  };

  room* here;
};

#endif