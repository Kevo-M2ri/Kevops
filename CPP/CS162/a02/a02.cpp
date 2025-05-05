#include <iostream>
#include <string>
#include <filesystem>
#include "stb_vorbis.c"

using namespace std;
// Use this for handling folders
namespace fs = filesystem;

// Song class to store song information
class Song {
private:
    string filePath; // Path to the song file
    string title;    // Song title
    string artist;   // Song artist
    string album;    // Song album
    int trackNumber;      // Track number
    float duration;       // Song length in seconds

public:
    // Set default values
    Song() {
        title = "Unknown Title";
        artist = "Unknown Artist";
        album = "Unknown Album";
        trackNumber = 0;
        duration = 0.0;
    }

    // Get song details
    string getFilePath() { return filePath; }
    string getTitle() { return title; }
    string getArtist() { return artist; }
    string getAlbum() { return album; }
    int getTrackNumber() { return trackNumber; }
    float getDuration() { return duration; }

    // Set song details
    void setFilePath(string path) { filePath = path; }
    void setTitle(string t) { title = t; }
    void setArtist(string a) { artist = a; }
    void setAlbum(string a) { album = a; }
    void setTrackNumber(int t) { trackNumber = t; }
    void setDuration(float d) { duration = d; }

    // Show song info
    void display() {
        cout << "Title: " << title << "\n";
        cout << "Artist: " << artist << "\n";
        cout << "Album: " << album << "\n";
        cout << "Track Number: " << trackNumber << "\n";
        cout << "Duration: " << duration << " seconds\n";
        cout << "File: " << filePath << "\n";
    }
};

// Playlist class to store songs
class Playlist {
private:
    string name;       // Playlist name
    Song songs[100];        // Array to hold up to 100 songs
    int numSongs;           // How many songs are in the array

public:
    // Set playlist name and start with no songs
    Playlist(string n) {
        name = n;
        numSongs = 0;
    }

    // Get playlist name
    string getName() { return name; }

    // Add a song to the playlist
    bool addSong(Song song) {
        if (numSongs >= 100) {
            cout << "Playlist is full! Cannot add more songs.\n";
            return false;
        }
        songs[numSongs] = song;
        numSongs++;
        cout << "Added song: " << song.getTitle() << "\n";
        return true;
    }

    // Remove a song by title
    bool removeSong(string title) {
        for (int i = 0; i < numSongs; i++) {
            if (songs[i].getTitle() == title) {
                // Shift songs to fill the gap
                for (int j = i; j < numSongs - 1; j++) {
                    songs[j] = songs[j + 1];
                }
                numSongs--;
                return true; // Found and removed
            }
        }
        return false; // Not found
    }

    // Show all songs in the playlist
    void displaySongs() {
        if (numSongs == 0) {
            cout << "Playlist '" << name << "' is empty.\n";
            return;
        }
        cout << "Playlist '" << name << "':\n";
        for (int i = 0; i < numSongs; i++) {
            cout << (i + 1) << ". " << songs[i].getTitle() << " by " << songs[i].getArtist() << "\n";
        }
    }

    // Get a song by index (for adding to playlist)
    Song getSong(int index) {
        if (index >= 0 && index < numSongs) {
            return songs[index];
        }
        return Song(); // Return empty song if index is invalid
    }

    // Get number of songs
    int getNumSongs() { return numSongs; }
};

// Make a string all uppercase
string toUpper(string str) {
    for (char& c : str) {
        if (c >= 'a' && c <= 'z') {
            c = c - 32; // Change to uppercase
        }
    }
    return str;
}

// Read title, artist, album, and track number from an Ogg file
bool parseOggMetadata(string filePath, Song& song) {
    int error;
    stb_vorbis* vorbis = stb_vorbis_open_filename(filePath.c_str(), &error, NULL);

    if (!vorbis) {
        cout << "Error: Could not open file " << filePath << "\n";
        return false;
    }

    // Get song length
    float duration = stb_vorbis_stream_length_in_seconds(vorbis);
    song.setFilePath(filePath);
    song.setDuration(duration);
    // Use filename without .ogg as default title
    string filename = filePath.substr(filePath.find_last_of("/\\") + 1);
    if (filename.length() >= 4 && filename.substr(filename.length() - 4) == ".ogg") {
        filename = filename.substr(0, filename.length() - 4);
    }
    song.setTitle(filename);
    song.setArtist("Unknown Artist");
    song.setAlbum("Unknown Album");
    song.setTrackNumber(0);

    // Get comments (title, artist, album, track number)
    stb_vorbis_comment comment = stb_vorbis_get_comment(vorbis);
    for (int i = 0; i < comment.comment_list_length; i++) {
        string commentStr = comment.comment_list[i];
        string commentUpper = toUpper(commentStr);

        if (commentUpper.find("TITLE=") == 0) {
            song.setTitle(commentStr.substr(6)); // Text after "TITLE="
        }
        else if (commentUpper.find("ARTIST=") == 0) {
            song.setArtist(commentStr.substr(7)); // Text after "ARTIST="
        }
        else if (commentUpper.find("ALBUM=") == 0) {
            song.setAlbum(commentStr.substr(6)); // Text after "ALBUM="
        }
        else if (commentUpper.find("TRACKNUMBER=") == 0) {
            string trackStr = commentStr.substr(12); // Text after "TRACKNUMBER="
            try {
                int track = std::stoi(trackStr);
                song.setTrackNumber(track);
            } catch (...) {
                // Keep default (0) if not a number
            }
        }
    }

    stb_vorbis_close(vorbis);
    return true;
}

// Load songs from a folder into an array
bool loadSongsFromDirectory(string directory, Song masterList[], int& numSongs) {
    numSongs = 0; // Start with 0 songs

    // Look at each file in the folder
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.path().extension() == ".ogg") {
            if (numSongs >= 100) {
                cout << "Too many songs! Only 100 can be loaded.\n";
                return false;
            }
            Song song;
            if (parseOggMetadata(entry.path().string(), song)) {
                masterList[numSongs] = song;
                numSongs++;
            }
        }
    }
    return true;
}

// Show playlist menu
void playlistMenu(Playlist& currentPlaylist, Song masterList[], int numMasterSongs) {
    while (true) {
        cout << "\nPlaylist Menu:\n";
        cout << "1. Show playlist\n";
        cout << "2. Add song\n";
        cout << "3. Remove song\n";
        cout << "4. Back to main menu\n";
        cout << "Enter choice (1-4): ";

        string choice;
        getline(cin, choice);

        if (choice.empty()) {
            cout << "Please enter a number.\n";
            continue;
        }

        if (choice == "1") {
            currentPlaylist.displaySongs();
        }
        else if (choice == "2") {
            if (numMasterSongs == 0) {
                cout << "No songs available. Load some songs first.\n";
                continue;
            }

            cout << "Songs you can add:\n";
            for (int i = 0; i < numMasterSongs; i++) {
                cout << (i + 1) << ". " << masterList[i].getTitle() << " by " << masterList[i].getArtist() << "\n";
            }

            cout << "Enter song number (or 0 to cancel): ";
            string songNumber;
            getline(cin, songNumber);

            if (songNumber.empty()) {
                cout << "Please enter a number.\n";
                continue;
            }

            int num;
            try {
                num = stoi(songNumber);
            } catch (...) {
                cout << "Please enter a valid number.\n";
                continue;
            }

            if (num == 0) {
                cout << "Cancelled.\n";
            }
            else if (num >= 1 && num <= numMasterSongs) {
                currentPlaylist.addSong(masterList[num - 1]);
            }
            else {
                cout << "Invalid number. Choose between 1 and " << numMasterSongs << ".\n";
            }
        }
        else if (choice == "3") {
            cout << "Enter song title to remove: ";
            string title;
            getline(cin, title);

            if (title.empty()) {
                cout << "Title cannot be empty.\n";
                continue;
            }

            if (currentPlaylist.removeSong(title)) {
                cout << "Removed song: " << title << "\n";
            }
            else {
                cout << "Song not found: " << title << "\n";
            }
        }
        else if (choice == "4") {
            break; // Go back to main menu
        }
        else {
            cout << "Invalid choice. Enter 1, 2, 3, or 4.\n";
        }
    }
}

int main() {
    Song masterList[100]; // Array for up to 100 songs
    int numMasterSongs = 0; // How many songs are loaded
    Playlist currentPlaylist("My Playlist"); // Our playlist

    // Main menu loop
    while (true) {
        cout << "\nMain Menu:\n";
        cout << "1. Load songs from folder\n";
        cout << "2. Show all songs\n";
        cout << "3. Manage playlist\n";
        cout << "4. Exit\n";
        cout << "Enter choice (1-4): ";

        string choice;
        getline(cin, choice);

        if (choice.empty()) {
            cout << "Please enter a number.\n";
            continue;
        }

        if (choice == "1") {
            cout << "Enter folder path: ";
            string folder;
            getline(cin, folder);

            if (folder.empty()) {
                cout << "Folder path cannot be empty.\n";
                continue;
            }

            if (loadSongsFromDirectory(folder, masterList, numMasterSongs)) {
                cout << "Loaded " << numMasterSongs << " songs.\n";
            }
        }
        else if (choice == "2") {
            if (numMasterSongs == 0) {
                cout << "No songs loaded.\n";
            }
            else {
                cout << "All songs:\n";
                for (int i = 0; i < numMasterSongs; i++) {
                    masterList[i].display();
                    cout << "-------------------\n";
                }
            }
        }
        else if (choice == "3") {
            playlistMenu(currentPlaylist, masterList, numMasterSongs);
        }
        else if (choice == "4") {
            cout << "Goodbye!\n";
            break;
        }
        else {
            cout << "Invalid choice. Enter 1, 2, 3, or 4.\n";
        }
    }

    return 0;
}