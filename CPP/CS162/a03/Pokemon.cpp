#include "Pokemon.h"
using namespace std;



bool isWeak(string attacking, string defending){

    if (attacking == "fire")
    {
        if (defending == "grass" || defending == "ice"
            || defending == "bug" || defending == "steel")
            return true;
    }
    else if (attacking == "water")
    {
        if (defending == "fire" || defending == "ground"
            || defending == "rock")
            return true;
    }
    else if (attacking == "electric")
    {
        if (defending == "water" || defending == "flying")
            return true;
    }
    else if (attacking == "grass")
    {
        if (defending == "water" || defending == "ground"
            || defending == "rock")
            return true;
    }
    else if (attacking == "ice")
    {
        if (defending == "grass" || defending == "ground"
            || defending == "flying" || defending == "dragon")
            return true;
    }
    else if (attacking == "fighting")
    {
        if (defending == "normal" || defending == "ice"
            || defending == "rock"   || defending == "dark"
            || defending == "steel")
            return true;
    }
    else if (attacking == "poison")
    {
        if (defending == "grass" || defending == "fairy")
            return true;
    }
    else if (attacking == "ground")
    {
        if (defending == "fire" || defending == "electric"
            || defending == "poison" || defending == "rock"
            || defending == "steel")
            return true;
    }
    else if (attacking == "flying")
    {
        if (defending == "grass" || defending == "fighting"
            || defending == "bug")
            return true;
    }
    else if (attacking == "psychic")
    {
        if (defending == "fighting" || defending == "poison")
            return true;
    }
    else if (attacking == "bug")
    {
        if (defending == "grass" || defending == "psychic"
            || defending == "dark")
            return true;
    }
    else if (attacking == "rock")
    {
        if (defending == "fire" || defending == "ice"
            || defending == "flying" || defending == "bug")
            return true;
    }
    else if (attacking == "ghost")
    {
        if (defending == "psychic" || defending == "ghost")
            return true;
    }
    else if (attacking == "dragon")
    {
        if (defending == "dragon")
            return true;
    }
    else if (attacking == "dark")
    {
        if (defending == "psychic" || defending == "ghost")
            return true;
    }
    else if (attacking == "steel")
    {
        if (defending == "ice" || defending == "rock"
            || defending == "fairy")
            return true;
    }
    else if (attacking == "fairy")
    {
        if (defending == "fighting" || defending == "dragon"
            || defending == "dark")
            return true;
    }
    /* Normal-type moves are not super-effective against anything,
       so no check is needed; we’ll just fall through.                */

    return false;
}

bool isStrong(string attacking, string defending){

    /* check every attack type’s “not-very-effective / no-effect” list */
    if (attacking == "fire")
    {
        if (defending == "fire"  || defending == "water"
            || defending == "rock" || defending == "dragon")
            return true;
    }
    else if (attacking == "water")
    {
        if (defending == "water" || defending == "grass"
            || defending == "dragon")
            return true;
    }
    else if (attacking == "electric")
    {
        if (defending == "electric" || defending == "grass"
            || defending == "dragon" || defending == "ground") // ground = immune
            return true;
    }
    else if (attacking == "grass")
    {
        if (defending == "fire" || defending == "grass"
            || defending == "poison" || defending == "flying"
            || defending == "bug" || defending == "dragon"
            || defending == "steel")
            return true;
    }
    else if (attacking == "ice")
    {
        if (defending == "fire" || defending == "water"
            || defending == "ice" || defending == "steel")
            return true;
    }
    else if (attacking == "fighting")
    {
        if (defending == "poison" || defending == "flying"
            || defending == "psychic" || defending == "bug"
            || defending == "fairy" || defending == "ghost")   // ghost = immune
            return true;
    }
    else if (attacking == "poison")
    {
        if (defending == "poison" || defending == "ground"
            || defending == "rock" || defending == "ghost"
            || defending == "steel")                           // steel = immune
            return true;
    }
    else if (attacking == "ground")
    {
        if (defending == "grass" || defending == "bug"
            || defending == "flying")                          // flying = immune
            return true;
    }
    else if (attacking == "flying")
    {
        if (defending == "electric" || defending == "rock"
            || defending == "steel")
            return true;
    }
    else if (attacking == "psychic")
    {
        if (defending == "psychic" || defending == "steel"
            || defending == "dark")                            // dark = immune
            return true;
    }
    else if (attacking == "bug")
    {
        if (defending == "fire" || defending == "fighting"
            || defending == "poison" || defending == "flying"
            || defending == "ghost" || defending == "steel"
            || defending == "fairy")
            return true;
    }
    else if (attacking == "rock")
    {
        if (defending == "fighting" || defending == "ground"
            || defending == "steel")
            return true;
    }
    else if (attacking == "ghost")
    {
        if (defending == "dark"  || defending == "normal")     // normal = immune
            return true;
    }
    else if (attacking == "dragon")
    {
        if (defending == "steel" || defending == "fairy")      // fairy = immune
            return true;
    }
    else if (attacking == "dark")
    {
        if (defending == "fighting" || defending == "dark"
            || defending == "fairy")
            return true;
    }
    else if (attacking == "steel")
    {
        if (defending == "fire" || defending == "water"
            || defending == "electric" || defending == "steel")
            return true;
    }
    else if (attacking == "fairy")
    {
        if (defending == "fire" || defending == "poison"
            || defending == "steel")
            return true;
    }
    else if (attacking == "normal")
    {
        if (defending == "rock" || defending == "steel"
            || defending == "ghost")                          // ghost = immune
            return true;
    }

    /* not resistant → return false */
    return false;
}

bool Pokemon::isWeakTo(string aType){
  bool type1Weak = isWeak(aType,type1);
  bool type2Weak = false;
  if(type2 != ""){
    type2Weak = isWeak(aType,type2);
  }

  return (type1Weak || type2Weak);
}

bool Pokemon::isStrongTo(string aType){
  bool type1Strong = isStrong(aType,type1);
  bool type2Strong = false;
  if(type2 != ""){
    type2Strong = isStrong(aType,type2);
  }

  return (type1Strong || type2Strong);
}