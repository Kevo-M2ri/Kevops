#ifndef TREASURE_H
#define TREASURE_H

#include <string>
using namespace std;

struct Treasure {
    string name;
    int worth;
    
    Treasure(string n, int w) : name(n), worth(w) {}
    Treasure() : name(""), worth(0) {}
};


#endif