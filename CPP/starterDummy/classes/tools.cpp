//This is the implementation file for tools.h
#include "tools.h"
#include "song.h"
//Function implementations

//displays the menu
void displayMenu()
{
   cout << "Welcome to the Song Database:" << endl << endl;
   cout << "Pick an option" << endl;
   cout << "[A-a]: Add a Song" << endl;
   cout << "[D-d]: Display the List" << endl;
   cout << "[T-t]: Find a song by title" << endl;
   cout << "[S-s]: Find a song by Artist" << endl;
   cout << "[R-r]: Remove a song" << endl;
   cout << "[Q-q]: Quit" << endl;
}

//read the option from the user
char readOption()
{
   char input;
   
   cin >> input;
   cin.ignore(100, '\n');
   
   return input;
}

//execute the option
void exeCmd(char option, SongList &playList)
{
   SongType aSong;
   switch (tolower(option))
   {
      case 'a': 
      {
         addSong(aSong);
         playList.addSong(aSong);
         break;
      }
      case 'd':
      {
         playList.showList();
         break;
      }
      case 'r':
      {
         playList.showList();
         playList.removeSong();
         break;
      }
      case 't':
      {
         playList.searchByTitle();
         break;
      }      
      case 's': 
      {
         playList.searchByArtist();
         break;
      }
      case 'q':
      {
         break;
      }
      default:
      {
         cout << "Invalid input, please try again!!" << endl;
      }
   }
}

//Name: readInt (reads and validates an integer)
//input: none
//output: error message
//return: int
int readInt(char prompt[])
{
   int temp = 0;
   
   cout << prompt;
   cin >> temp;
   
   //data validation
   while (!cin)
   {
      cin.clear();
      cin.ignore(100, '\n');
      cout << "Invalid input!! Please try again!!";
      cin >> temp;
   }
   
   cin.ignore(100, '\n');
   
   return temp;
}

//standalone overloaded addSong function
//populate aSong from the user
void addSong(SongType &aSong)
{
   char letter;
   char tempTitle[MAXCHAR], tempArtist[MAXCHAR];
   int tempDuration = 0;
   int tempBPS = 0;
   
   cout << "Enter a song name: ";
   cin.get(tempTitle, MAXCHAR, '\n');
   cin.ignore(100, '\n');
   cout << "Enter artist: ";
   cin.getline(tempArtist, MAXCHAR);
   tempDuration = readInt("Enter duration: ");
   tempBPS = readInt("Enter BPS: ");
   
   //populate aSong calling the mutator functions
   aSong.setSongTitle(tempTitle);
   aSong.setDuration(tempDuration);
   aSong.setSongArtist(tempArtist);
   aSong.setBPS(tempBPS);
}

//converts all text to upper case
void convertCase(char tempStr[])
{
   for (int i = 0; i < strlen(tempStr); i++)
   {
      tempStr[i] = toupper(tempStr[i]);
   }
}