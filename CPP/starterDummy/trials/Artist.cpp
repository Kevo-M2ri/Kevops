#include "Artist.h"
using namespace std;

Artist::Artist() {
   strcpy(artistName, "Unknown");
   birthYear = 0;
   deathYear = 0;
}

Artist::Artist(char *artistName, int birthYear, int deathYear) {
   strcpy(this->artistName, artistName);
   this->birthYear = birthYear;
   this->deathYear = deathYear;  
}

void Artist::GetName(char *returnName) const {
  strcpy(returnName, artistName);
}

int Artist::GetBirthYear() const {
  return birthYear;
}

int Artist::GetDeathYear() const {
  return deathYear;
}

void Artist::PrintInfo() const {
  cout << "Artist Name: " << artistName << endl;
  
  if (deathYear == -1) {
    cout << "Birth Year: " << birthYear << endl;
  }
  else {
    cout << "Birth Year: " << birthYear << endl;
    cout << "Death Year: " << deathYear << endl;
  }
}