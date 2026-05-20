//The driver file with main() to test the Song class.
#include "song.h"

//main
int main()
{
    SongType mySong("Put a ring on it", "Byonce", 4, 80);
    SongType yourSong("Yellow Submarine", "Beatles", 3, 70);
    char srchSong[MAXCHAR];
    //call isLonger method
    if(mySong.isLonger(yourSong))
    {
        mySong.printSong();
    }
    else
    {
        yourSong.printSong();
    }
    cout << "Enter the artist to search for: ";
    cin.getline(srchSong, MAXCHAR);
    //call the artist search method
    if(mySong.isArtist(srchSong))
    {
        mySong.printSong();
    }
    else
    {
        cout << "Artist not found in mySong!" << endl;
    }
    if(!yourSong.isArtist(srchSong))
    {
        cout << "Artist not found in yourSong!" << endl;
    }
    else
    {
        yourSong.printSong();
    }
    return 0;
}