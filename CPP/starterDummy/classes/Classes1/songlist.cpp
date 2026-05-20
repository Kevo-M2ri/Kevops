//This is the implementation file for the SongList class
#include "songlist.h"
#include "tools.h"

//constructors
SongList::SongList()
{
   size = 0;
}

//constructor from file
SongList::SongList(char fileName[])
{
   size = 0;
   ifstream inFile;
   SongType aSong;
   char tempTitle[MAXCHAR], tempArtist[MAXCHAR];
   int tempDuration;
   int tempBPS;
   
   inFile.open(fileName);
   
   if(!inFile)
   {
      cout << "cannot open file! Exiting!!" << endl;
      exit(0);
   }
   
   inFile.getline(tempTitle, MAXCHAR, ';');
   
   while(!inFile.eof())
   {
      inFile.getline(tempArtist, MAXCHAR, ';');
      inFile >> tempDuration;
      inFile.ignore(5, ';');
      inFile >> tempBPS;
      inFile.ignore(5, '\n');
      //populate aSong;
      aSong.setSongTitle(tempTitle);
      aSong.setSongArtist(tempArtist);
      aSong.setDuration(tempDuration);
      aSong.setBPS(tempBPS);
      addSong(aSong);
      inFile.getline(tempTitle, MAXCHAR, ';');
   }
   
   inFile.close();
}

//destructor
SongList::~SongList()
{
//nothing to do
}

//Add a song to the store
void SongList::addSong(SongType aSong)
{
   list[size++] = aSong;
}

//search by Title
void SongList::searchByTitle()
{
   char searchTitle[MAXCHAR];
   char tempTitle[MAXCHAR];
   
   cout << "Please enter title to search for:";
   cin.get(searchTitle, MAXCHAR);
   convertCase(searchTitle);
   
   for(int i = 0; i < size; i++)
   {
      list[i].getSongTitle(tempTitle);
      convertCase(tempTitle);
      if(strstr(tempTitle, searchTitle) != NULL)
      {
         list[i].printSong();
      }
   }
   
   cout << endl;
}

//search by Artist
void SongList::searchByArtist()
{
   char tempArtist[MAXCHAR], srchArtist[MAXCHAR];
   
   cout << "Please enter the artist to search for: ";
   cin.getline(srchArtist, MAXCHAR);
   
   for(int i = 0; i < size; i++)
   {
      list[i].getSongArtist(tempArtist);
      
      if(strstr(tempArtist, srchArtist) != NULL)
      {
         list[i].printSong();
      }
   }
	
	cout << endl;
}

//writes the data to the file
void SongList::writeData(char fileName[])
{
   ofstream outFile;
   outFile.open(fileName);
   
   for(int i = 0; i < size; i++)
   {
      list[i].printSong(outFile);
   }
}

//displays the list
void SongList::showList()
{
   for(int i = 0; i < size; i++)
   {
      cout << i+1 << ") ";
      list[i].printSong();
   }
   
   cout << endl;
}

//removes a song  from the list
void SongList::removeSong()
{
   int delIndex = 0;
   
   delIndex = readInt("Please enter index of song to delete:");
   
   if(delIndex < size)
   {
      for(int i = delIndex; i < size; i++)
      {
         list[i-1] = list[i];
      }
   }
   
   size--;
}