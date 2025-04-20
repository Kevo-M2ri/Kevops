//header file for the Song class
//has constructors, accessors, mutators and some functions
#pragma once
#include <iostream>
#include <cstring>
using namespace std;

const int MAXCHAR = 101;

//Song class
class SongType
{
private:
    char title[MAXCHAR];
    char artist[MAXCHAR];
    int duration;
    int BPS;
public:
    //constructors
    SongType();
    SongType(char [], char [], int, int);
    //accessor and mutator methods
    //mutators
    void setSongTitle(char *);
    void setSongArtist(char *);
    void setDuration(int);
    void setBPS(int);
    //accessor functions
    void getSongTitle(char *);
    void getSongArtist(char *);
    int getSongDuration();
    int getSongBPS();
    //bool method to compare duration
    bool isLonger(SongType);
    //method to compare artist and print a Song object
    bool isArtist(char *);
    void printSong();
};