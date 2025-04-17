#ifndef ARTISTH
#define ARTISTH

#include <cstring>
using namespace std;

class Artist{
   public:
      Artist();

      Artist(char *artistName, int birthYear, int deathYear);

      void GetName(char *returnName) const;

      int GetBirthYear() const;

      int GetDeathYear() const;

      void PrintInfo() const;
   
   private:
      // TODO: Declare private data members - artistName, birthYear, deathYear

};

#endif