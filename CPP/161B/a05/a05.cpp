#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <iomanip>
using namespace std;

const int MAX_CHAR = 35;
const int MAX_SIZE = 15;
const string fileName = "Cybersecurity.csv";

void openFile(ifstream &file, const string &fileName);
void printLists(const char country[][MAX_CHAR], const int gci[], const int ncsi[], int size);
void doAnalysis(const int ncsi[], const char[][MAX_CHAR], int size);
void calcAverage(const int gci[], int size);

int main() {
    char country[MAX_SIZE][MAX_CHAR];
    int gci[MAX_SIZE];
    int ncsi[MAX_SIZE];
    int size = 0;
    string line;
    string countryName;

    ifstream inputFile;
    openFile(inputFile, fileName);

    while (getline(inputFile, line)) {
        size_t pos1 = line.find(','); // Find the first comma
        size_t pos2 = line.find(',', pos1 + 1); // Find the second comma

        countryName = line.substr(0, pos1); // Extract country name
        strncpy(country[size], countryName.c_str(), MAX_CHAR - 1); // Copy country name
        country[size][MAX_CHAR - 1] = '\0'; // Ensure null-termination
        gci[size] = stoi(line.substr(pos1 + 1, pos2 - pos1 - 1)); // Extract GCI
        ncsi[size] = stoi(line.substr(pos2 + 1)); // Extract NCSI
        size++;
    }   
    
    inputFile.close();

    printLists(country, gci, ncsi, size);
    cout << endl;
    doAnalysis(ncsi, country, size);
    cout << endl;
    calcAverage(gci, size);
    cout << endl;

    return 0;
}

void openFIle(ifstream &file, const string&fileName) {
    file.open(fileName);
    if (!file.is_open()) {
        cout << "Error! File could not be opened." << endl;
        exit(1);
    }
}

void printLists(const char country[][MAX_CHAR], const int gci[], const int ncsi[], int size) {
    cout << setw(20) << left << "Country" << setw(15) << right << "GCI" << "NCSI" << endl;
    cout << "----------------------------------------" << endl;
    for (int i = 0; i < size; i++) {
        cout << setw(10) << country[i] << "\t" << gci[i] << "\t" << ncsi[i] << endl;
    }
}

void doAnalysis(const int ncsi[], const char country[][MAX_CHAR], int size) {
    int minIndex = 0, maxIndex = 0;
    double total = 0.0, average = 0.0;

    for (int i = 0; i < size; i++) {
        total += ncsi[i];
        if (ncsi[i] < ncsi[minIndex]) {
            minIndex = i;
        }
        if (ncsi[i] > ncsi[maxIndex]) {
            maxIndex = i;
        }
    }

    average = total / size;
    cout << "The average NCSI is: " << average << endl;
    cout << "The country with the highest NCSI is: " << country[maxIndex] << endl;
    cout << "The country with the lowest NCSI is: " << country[minIndex] << endl;
}

void calcAverage(const int gci[], int size) {
    double total = 0.0, average = 0.0;
    for (int i = 0; i < size; i++) {
        total += gci[i];
    }
    average = total / size;
    cout << "The average GCI is: " << average << endl;
}