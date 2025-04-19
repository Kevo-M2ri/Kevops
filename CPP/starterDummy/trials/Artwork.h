#ifndef ARTWORKH
#define ARTWORKH

#include "Artist.h"

class Artwork{
   public:
      Artwork();

      Artwork(char *newTitle, int newYearCreated, Artist newArtist);
      void GetTitle(char *returnTitle);

      int GetYearCreated();

      void PrintInfo();

   private:
      char title[101];
      int yearCreated;
      Artist artist;
};

#endif