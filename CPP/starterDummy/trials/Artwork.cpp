#include "Artwork.h"

Artwork::Artwork() {
   strcpy(title, "Unknown");
   yearCreated = 0;
}

Artwork::Artwork(char *title, int yearCreated, Artist artist) {
   strcpy(this->title, title);
   this->yearCreated = yearCreated;
   this->artist = artist;
}

void Artwork::GetTitle(char* returnTitle) {
  strcpy(returnTitle, title);
}

int Artwork::GetYearCreated() {
  return yearCreated;
}

void Artwork::PrintInfo() {
  cout << "Title: " << title;
  cout << "Year created: " << yearCreated << endl;
  artist.PrintInfo();
}