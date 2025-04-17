#include "Artist.h"
#include "Artwork.h"
#include <iostream>
#include <cstring>
using namespace std;

int main() {
   char userTitle[101], userArtistName[101];
   int yearCreated, userBirthYear, userDeathYear;

   cin.getline(userArtistName, 101);
   cin >> userBirthYear;
   cin.ignore();
   cin >> userDeathYear;
   cin.ignore();
   cin.getline(userTitle, 101);
   cin >> yearCreated;
   cin.ignore();

   Artist userArtist =  Artist(userArtistName, userBirthYear, userDeathYear);

   Artwork newArtwork = Artwork(userTitle, yearCreated, userArtist);

   newArtwork.PrintInfo();
}