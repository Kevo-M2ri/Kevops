#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <filesystem>
#include <memory>
#include <iomanip>

// Include the stb_vorbis library
// In a real implementation, you would download the complete stb_vorbis.c from:
// https://github.com/nothings/stb/blob/master/stb_vorbis.c
#define STB_VORBIS_IMPLEMENTATION
#include "stb_vorbis.h"

// Song class to store metadata for each track
class Song {
private:
    std::string filePath;
    std::string title;
    std::string artist;
    std::string album;
    std::string genre;
    std::string year;
    int trackNumber;
    float duration;

public:
    // Default constructor
    Song() : trackNumber(0), duration(0.0f) {}

    // Constructor with parameters
    Song(const std::string& path, const std::string& t, const std::string& art,
         const std::string& alb, const std::string& gen, const std::string& yr,
         int track, float dur)
        : filePath(path), title(t), artist(art), album(alb), genre(gen),
          year(yr), trackNumber(track), duration(dur) {}

    // Getters
    std::string getFilePath() const { return filePath; }
    std::string getTitle() const { return title; }
    std::string getArtist() const { return artist; }
    std::string getAlbum() const { return album; }
    std::string getGenre() const { return genre; }
    std::string getYear() const { return year; }
    int getTrackNumber() const { return trackNumber; }
    float getDuration() const { return duration; }

    // Setters
    void setFilePath(const std::string& path) { filePath = path; }
    void setTitle(const std::string& t) { title = t; }
    void setArtist(const std::string& art) { artist = art; }
    void setAlbum(const std::string& alb) { album = alb; }
    void setGenre(const std::string& gen) { genre = gen; }
    void setYear(const std::string& yr) { year = yr; }
    void setTrackNumber(int track) { trackNumber = track; }
    void setDuration(float dur) { duration = dur; }

    // Display song information
    void display() const {
        std::cout << "Title: " << title << std::endl;
        std::cout << "Artist: " << artist << std::endl;
        std::cout << "Album: " << album << std::endl;
        if (trackNumber > 0) {
            std::cout << "Track: " << trackNumber << std::endl;
        }
        if (!genre.empty()) {
            std::cout << "Genre: " << genre << std::endl;
        }
        if (!year.empty()) {
            std::cout << "Year: " << year << std::endl;
        }
        std::cout << "Duration: " << int(duration / 60) << ":" 
                  << std::setfill('0') << std::setw(2) << int(duration) % 60 << std::endl;
        std::cout << "File: " << filePath << std::endl;
        std::cout << "-------------------------" << std::endl;
    }
};

// Playlist class to manage collections of songs
class Playlist {
private:
    std::string playlistName;
    std::vector<Song> songs;

public:
    // Default constructor
    Playlist() : playlistName("New Playlist") {}
    
    // Constructor with name
    Playlist(const std::string& name) : playlistName(name) {}
    
    // Getters
    std::string getName() const { return playlistName; }
    std::vector<Song> getSongs() const { return songs; }
    
    // Setters
    void setName(const std::string& name) { playlistName = name; }
    
    // Add a song to the playlist
    void addSong(const Song& song) {
        songs.push_back(song);
    }
    
    // Remove a song by title
    bool removeSong(const std::string& title) {
        for (auto it = songs.begin(); it != songs.end(); ++it) {
            if (it->getTitle() == title) {
                songs.erase(it);
                return true;
            }
        }
        return false;
    }
    
    // Clear all songs from the playlist
    void clear() {
        songs.clear();
    }
    
    // Get number of songs in the playlist
    size_t size() const {
        return songs.size();
    }
    
    // Filter the playlist by artist
    Playlist filterByArtist(const std::string& artist) const {
        Playlist filtered(playlistName + " (Filtered)");
        for (const auto& song : songs) {
            if (song.getArtist() == artist) {
                filtered.addSong(song);
            }
        }
        return filtered;
    }
    
    // Filter the playlist by genre
    Playlist filterByGenre(const std::string& genre) const {
        Playlist filtered(playlistName + " (Filtered)");
        for (const auto& song : songs) {
            if (song.getGenre() == genre) {
                filtered.addSong(song);
            }
        }
        return filtered;
    }
    
    // Export the playlist to a .m3u file
    bool exportToM3U(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            return false;
        }
        
        // Write .m3u header
        outFile << "#EXTM3U" << std::endl;
        
        // Write each song
        for (const auto& song : songs) {
            outFile << "#EXTINF:" << int(song.getDuration()) << "," 
                    << song.getArtist() << " - " << song.getTitle() << std::endl;
            outFile << song.getFilePath() << std::endl;
        }
        
        outFile.close();
        return true;
    }
    
    // Display all songs in the playlist
    void displaySongs() const {
        std::cout << "Playlist: " << playlistName << " (" << songs.size() << " songs)" << std::endl;
        std::cout << "=========================" << std::endl;
        
        for (const auto& song : songs) {
            song.display();
        }
    }
};

// Function to parse metadata from an .ogg file
bool parseOggMetadata(const std::string& filePath, Song& song) {
    int error;
    stb_vorbis* vorbis = stb_vorbis_open_filename(filePath.c_str(), &error, nullptr);
    
    if (!vorbis) {
        std::cerr << "Error opening file: " << filePath << " (Error code: " << error << ")" << std::endl;
        return false;
    }
    
    // Get basic info
    stb_vorbis_info info = stb_vorbis_get_info(vorbis);
    
    // Calculate duration
    float duration = stb_vorbis_stream_length_in_seconds(vorbis);
    
    // Set the file path and duration
    song.setFilePath(filePath);
    song.setDuration(duration);
    
    // Extract metadata
    int commentCount;
    const char** comments = stb_vorbis_get_comment_list(vorbis, &commentCount);
    
    // Set defaults
    song.setTitle(std::filesystem::path(filePath).filename().string());
    song.setArtist("Unknown Artist");
    song.setAlbum("Unknown Album");
    song.setGenre("");
    song.setYear("");
    song.setTrackNumber(0);
    
    // Parse the comments for metadata
    for (int i = 0; i < commentCount; i++) {
        std::string comment(comments[i]);
        
        // Check for title
        if (comment.find("TITLE=") == 0) {
            song.setTitle(comment.substr(6));
        }
        // Check for artist
        else if (comment.find("ARTIST=") == 0) {
            song.setArtist(comment.substr(7));
        }
        // Check for album
        else if (comment.find("ALBUM=") == 0) {
            song.setAlbum(comment.substr(6));
        }
        // Check for track number
        else if (comment.find("TRACKNUMBER=") == 0) {
            try {
                song.setTrackNumber(std::stoi(comment.substr(12)));
            } catch (const std::exception& e) {
                // If parsing fails, keep default value
            }
        }
        // Check for genre
        else if (comment.find("GENRE=") == 0) {
            song.setGenre(comment.substr(6));
        }
        // Check for year
        else if (comment.find("DATE=") == 0 || comment.find("YEAR=") == 0) {
            size_t pos = comment.find("DATE=") == 0 ? 5 : 5;
            song.setYear(comment.substr(pos));
        }
    }
    
    stb_vorbis_close(vorbis);
    return true;
}

// Function to load all .ogg files from a directory
std::vector<Song> loadSongsFromDirectory(const std::string& directory) {
    std::vector<Song> songs;
    
    try {
        for (const auto& entry : std::filesystem::directory_iterator(directory)) {
            if (entry.path().extension() == ".ogg") {
                Song song;
                if (parseOggMetadata(entry.path().string(), song)) {
                    songs.push_back(song);
                }
            }
        }
    } catch (const std::filesystem::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
    }
    
    return songs;
}

// Comparator functions for sorting
bool compareByTitle(const Song& a, const Song& b) {
    return a.getTitle() < b.getTitle();
}

bool compareByArtist(const Song& a, const Song& b) {
    return a.getArtist() < b.getArtist();
}

bool compareByAlbum(const Song& a, const Song& b) {
    return a.getAlbum() < b.getAlbum();
}

bool compareByDuration(const Song& a, const Song& b) {
    return a.getDuration() < b.getDuration();
}

// Main function
int main() {
    std::vector<Song> masterList;
    Playlist currentPlaylist("Current Playlist");
    std::string input;
    
    std::cout << "OGG Playlist Manager" << std::endl;
    std::cout << "===================" << std::endl;
    
    while (true) {
        std::cout << "\nMain Menu:" << std::endl;
        std::cout << "1. Load .ogg files from directory" << std::endl;
        std::cout << "2. Add a single .ogg file" << std::endl;
        std::cout << "3. Sort master list" << std::endl;
        std::cout << "4. Search/filter songs" << std::endl;
        std::cout << "5. Display all songs" << std::endl;
        std::cout << "6. Playlist options" << std::endl;
        std::cout << "7. Quit" << std::endl;
        std::cout << "Choose an option: ";
        
        std::getline(std::cin, input);
        
        if (input == "1") {
            std::cout << "Enter directory path: ";
            std::string directory;
            std::getline(std::cin, directory);
            
            std::vector<Song> newSongs = loadSongsFromDirectory(directory);
            masterList.insert(masterList.end(), newSongs.begin(), newSongs.end());
            
            std::cout << "Loaded " << newSongs.size() << " songs." << std::endl;
        }
        else if (input == "2") {
            std::cout << "Enter .ogg file path: ";
            std::string filePath;
            std::getline(std::cin, filePath);
            
            Song song;
            if (parseOggMetadata(filePath, song)) {
                masterList.push_back(song);
                std::cout << "Added: " << song.getTitle() << " by " << song.getArtist() << std::endl;
            }
        }
        else if (input == "3") {
            std::cout << "Sort by:" << std::endl;
            std::cout << "1. Title" << std::endl;
            std::cout << "2. Artist" << std::endl;
            std::cout << "3. Album" << std::endl;
            std::cout << "4. Duration" << std::endl;
            std::cout << "Choose an option: ";
            
            std::string sortOption;
            std::getline(std::cin, sortOption);
            
            if (sortOption == "1") {
                std::sort(masterList.begin(), masterList.end(), compareByTitle);
                std::cout << "Sorted by title." << std::endl;
            }
            else if (sortOption == "2") {
                std::sort(masterList.begin(), masterList.end(), compareByArtist);
                std::cout << "Sorted by artist." << std::endl;
            }
            else if (sortOption == "3") {
                std::sort(masterList.begin(), masterList.end(), compareByAlbum);
                std::cout << "Sorted by album." << std::endl;
            }
            else if (sortOption == "4") {
                std::sort(masterList.begin(), masterList.end(), compareByDuration);
                std::cout << "Sorted by duration." << std::endl;
            }
        }
        else if (input == "4") {
            std::cout << "Search/filter by:" << std::endl;
            std::cout << "1. Title" << std::endl;
            std::cout << "2. Artist" << std::endl;
            std::cout << "3. Album" << std::endl;
            std::cout << "4. Genre" << std::endl;
            std::cout << "Choose an option: ";
            
            std::string filterOption;
            std::getline(std::cin, filterOption);
            
            std::cout << "Enter search term: ";
            std::string searchTerm;
            std::getline(std::cin, searchTerm);
            
            std::vector<Song> results;
            
            if (filterOption == "1") {
                for (const auto& song : masterList) {
                    if (song.getTitle().find(searchTerm) != std::string::npos) {
                        results.push_back(song);
                    }
                }
            }
            else if (filterOption == "2") {
                for (const auto& song : masterList) {
                    if (song.getArtist().find(searchTerm) != std::string::npos) {
                        results.push_back(song);
                    }
                }
            }
            else if (filterOption == "3") {
                for (const auto& song : masterList) {
                    if (song.getAlbum().find(searchTerm) != std::string::npos) {
                        results.push_back(song);
                    }
                }
            }
            else if (filterOption == "4") {
                for (const auto& song : masterList) {
                    if (song.getGenre().find(searchTerm) != std::string::npos) {
                        results.push_back(song);
                    }
                }
            }
            
            std::cout << "Found " << results.size() << " matching songs:" << std::endl;
            for (const auto& song : results) {
                song.display();
            }
            
            std::cout << "Add all to current playlist? (y/n): ";
            std::string addOption;
            std::getline(std::cin, addOption);
            
            if (addOption == "y" || addOption == "Y") {
                for (const auto& song : results) {
                    currentPlaylist.addSong(song);
                }
                std::cout << "Added " << results.size() << " songs to playlist." << std::endl;
            }
        }
        else if (input == "5") {
            std::cout << "All Songs (" << masterList.size() << "):" << std::endl;
            std::cout << "====================" << std::endl;
            
            for (const auto& song : masterList) {
                song.display();
            }
        }
        else if (input == "6") {
            std::cout << "\nPlaylist Menu:" << std::endl;
            std::cout << "1. Display current playlist" << std::endl;
            std::cout << "2. Add a song from master list" << std::endl;
            std::cout << "3. Remove a song from playlist" << std::endl;
            std::cout << "4. Clear playlist" << std::endl;
            std::cout << "5. Export playlist to .m3u" << std::endl;
            std::cout << "6. Rename playlist" << std::endl;
            std::cout << "7. Back to main menu" << std::endl;
            std::cout << "Choose an option: ";
            
            std::string playlistOption;
            std::getline(std::cin, playlistOption);
            
            if (playlistOption == "1") {
                currentPlaylist.displaySongs();
            }
            else if (playlistOption == "2") {
                if (masterList.empty()) {
                    std::cout << "Master list is empty. Please load some songs first." << std::endl;
                    continue;
                }
                
                std::cout << "Available songs:" << std::endl;
                for (size_t i = 0; i < masterList.size(); ++i) {
                    std::cout << i + 1 << ". " << masterList[i].getTitle() 
                              << " by " << masterList[i].getArtist() << std::endl;
                }
                
                std::cout << "Enter song number to add (or 0 to cancel): ";
                std::string songNumber;
                std::getline(std::cin, songNumber);
                
                try {
                    int num = std::stoi(songNumber);
                    if (num > 0 && num <= static_cast<int>(masterList.size())) {
                        currentPlaylist.addSong(masterList[num - 1]);
                        std::cout << "Added: " << masterList[num - 1].getTitle() << std::endl;
                    }
                } catch (const std::exception& e) {
                    std::cout << "Invalid input." << std::endl;
                }
            }
            else if (playlistOption == "3") {
                if (currentPlaylist.size() == 0) {
                    std::cout << "Playlist is empty." << std::endl;
                    continue;
                }
                
                std::cout << "Enter title of song to remove: ";
                std::string titleToRemove;
                std::getline(std::cin, titleToRemove);
                
                if (currentPlaylist.removeSong(titleToRemove)) {
                    std::cout << "Removed: " << titleToRemove << std::endl;
                } else {
                    std::cout << "Song not found in playlist." << std::endl;
                }
            }
            else if (playlistOption == "4") {
                currentPlaylist.clear();
                std::cout << "Playlist cleared." << std::endl;
            }
            else if (playlistOption == "5") {
                if (currentPlaylist.size() == 0) {
                    std::cout << "Playlist is empty." << std::endl;
                    continue;
                }
                
                std::cout << "Enter filename for .m3u file: ";
                std::string m3uFilename;
                std::getline(std::cin, m3uFilename);
                
                if (!m3uFilename.empty()) {
                    if (m3uFilename.find(".m3u") == std::string::npos) {
                        m3uFilename += ".m3u";
                    }
                    
                    if (currentPlaylist.exportToM3U(m3uFilename)) {
                        std::cout << "Playlist exported to " << m3uFilename << std::endl;
                    } else {
                        std::cout << "Error exporting playlist." << std::endl;
                    }
                }
            }
            else if (playlistOption == "6") {
                std::cout << "Enter new playlist name: ";
                std::string newName;
                std::getline(std::cin, newName);
                
                if (!newName.empty()) {
                    currentPlaylist.setName(newName);
                    std::cout << "Playlist renamed to: " << newName << std::endl;
                }
            }
            else if (playlistOption == "7") {
                // Return to main menu
                continue;
            }
        }
        else if (input == "7") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid option. Please try again." << std::endl;
        }
    }
    
    return 0;
}