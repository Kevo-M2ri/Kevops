#ifndef ARTISTH
#define ARTISTH

#include <iostream>
#include <cstring>
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
      char artistName[101];
      int birthYear;
      int deathYear;
};

#endif