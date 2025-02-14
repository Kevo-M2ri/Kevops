#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
using namespace std;

void readData(const char fileName[], char labels[][MAX_STR], int col1[], int col2[], int col3[], int &count);
void printData(const char title[], char labels[][MAX_STR], int col1[], int col2[], int col3[], int count);
void findMaxMin(char labels[][MAX_STR], int col1[], int count);
void calculateAverages(int col1[], int col2[], int col3[], int count);

const int MAX_ROWS = 40;
const int MAX_STR = 50;

int main() {
    char labels[MAX_ROWS][MAX_STR];
    int col1[MAX_ROWS], col2[MAX_ROWS], col3[MAX_ROWS], count;

    const char files[][MAX_STR] = {"salaries.csv", "automobile.csv", "disease.csv", "sleep_and_lifestyle.csv", "spotify_world.csv", "cybersecurity.csv"};
    const char titles[][MAX_STR] = {"Salaries.data", "Automobile.data", "Disease.data", "Sleep and Lifestyle.data", "Spotify World.data", "Cybersecurity.data"};
    
    for (int i = 0; i < 6; i++) {
        readData(files[i], labels, col1, col2, col3, count);
        printData(titles[i], labels, col1, col2, col3, count);
        findMaxMin(labels, col1, count);
        calculateAverages(col1, col2, col3, count);
    }
    return 0;
}

void readData(const char fileName[], char labels[][MAX_STR], int col1[], int col2[], int col3[], int &count) {
    ifstream file;
    char line[MAX_STR];

    file.open(fileName);
    if (!file) {
        cout << "Error opening file " << fileName << endl;
        exit(1);
    }
    file.getline(line, MAX_STR);
    count = 0;
    while (file.getline(line, MAX_STR) && count < MAX_ROWS) {
        
        count++;
    }
    file.close();
}