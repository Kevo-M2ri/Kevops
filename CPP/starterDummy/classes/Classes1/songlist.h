//class definition for a list of songs and its size
#pragma once
#include "song.h"

//constants
const int CAP = 50;

//define class SongList for array of songs and size

class SongList
{
private:
   SongType list[CAP];
   int size;
   
public:
   //constructors
   SongList();
   SongList(char []);
   
   //destructor
   ~SongList();
   
   //database functions
   void addSong(SongType);
   void searchByTitle();
   void searchByArtist();
   void showList();
   void removeSong();
   void writeData(char []);
};