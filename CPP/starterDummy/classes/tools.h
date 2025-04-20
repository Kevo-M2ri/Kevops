#ifndef TOOLS_H
#define TOOLS_H

#include "song.h"
#include "songlist.h"

//function prototypes
int readInt(char prompt[]);
void displayMenu();
char readOption();
void exeCmd(char option, SongList &);
void addSong(SongType &);
void convertCase(char tempStr[]);

#endif