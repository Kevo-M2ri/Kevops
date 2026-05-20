//The implementation file for song.h
#include "song.h"

//constructors
//default constructor
SongType::SongType()
{
    strcpy(title, "no title");
    strcpy(artist, "no artist");
    duration = 0;
    BPS = 0;
}

//constructor with parameters
SongType::SongType(char newTitle[], char newArtist[], int newDuration, int newBPS)
{
    strcpy(title, newTitle);
    strcpy(artist, newArtist);
    duration = newDuration;
    BPS = newBPS;
}

//mutator functions
void SongType::setSongTitle(char *newTitle)
{
    strcpy(title, newTitle);
}

void SongType::setSongArtist(char *newArtist)
{
    strcpy(artist, newArtist);
}

void SongType::setDuration(int newDuration)
{
    duration = newDuration;
}

void SongType::setBPS(int newBPS)
{
    BPS = newBPS;
}

//accessor functions
void SongType::getSongTitle(char *returnTitle)
{
    strcpy(returnTitle, title);
}

void SongType::getSongArtist(char *returnArtist)
{
    strcpy(returnArtist, artist);
}

int SongType::getSongDuration()
{
    return duration;
}

int SongType::getSongBPS()
{
    return BPS;
}

//comparison method for durations for 2 songs
bool SongType::isLonger(SongType aSong)
{
    if(duration > aSong.duration)
        return true;
    else
        return false;
}

//search for an artist name and print the song if it exists
bool SongType::isArtist(char *srchArtist)
{
    if(strstr(artist, srchArtist) != NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//print the song
void SongType::printSong()
{
    cout << title << ';' << artist << ';' << duration << ';' << BPS << endl;
}