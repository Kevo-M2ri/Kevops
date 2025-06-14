#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <string>
#include "Attack.h"
using namespace std;

class Creature {
private:
    string name;
    int hp;
    vector<Attack> moves;

public:
    Creature(string n, int health);

    string getName;
    int getHp() const;
    bool isAlive() const;

    void takeDamage(int damage);
    void addMove(const Attack& attack);
    vector<Attack> getMoves() const;
    Attack getRandomMove() const;

    void printStats() const;
};

#endif
```

---

### 5. Correcting `Creature.cpp`
**Issues:**
- **Compilation error**: In `Creature.h`, the getter function is declared as `getName` but defined in `Creature.cpp` as `getName`. Similarly, `getHp` is declared but defined as `getHp`.
- Missing include for `<vector>` since `vector<Attack>` is used.

**Solution:**
- Correct the function declarations in `Creature.h` to match the definitions in `Creature.cpp`.
- Add `#include <vector>`.

<xaiArtifact artifact_id="405dd1c8-ec5e-49d1-b6b3-0ea814a1d756" artifact_version_id="8ed9dfdf-4051-4c6f-b6f1-b17ef5cb4a83" title="Creature.h" contentType="text/cpp">
#ifndef CREATURE_H
#define CREATURE_H

#include <vector>
#include <string>
#include "Attack.h"
using namespace std;

class Creature {
private:
    string name;
    int hp;
    vector<Attack> moves;

public:
    Creature(string n, int health);

    string getName() const;
    int getHp() const;
    bool isAlive() const;

    void takeDamage(int damage);
    void addMove(const Attack& attack);
    vector<Attack> getMoves() const;
    Attack getRandomMove() const;

    void printStats() const;
};

#endif