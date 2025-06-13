#include "Map.h"
#include "Player.h"
#include "Creature.h"
#include "Attack.h"

// include anything else you need in here

using namespace std;

void initMap(Map &m){
  // this is an example of how to handle adding things to the dungeon before you start
  // it won't compile until you add all the necessary bits
  /*
  m.addCreature(makeGoblin());
  m.addLoot({"A golden pencil", 10000});
  m.addEast("A lounge with an ominous aura");
  m.moveEast();
  m.addCreature(makeAngryCompiler());
  m.addLoot({"A silky chicken", 100000000000});
  m.addNorth("The watercooler of the damned");
  m.moveWest(); // need to go back to the start
  
  */
}

int main(){
  Map m = Map("The dark entryway of the dungeon stretches out before you");
  initMap(m);
  return 0;
}