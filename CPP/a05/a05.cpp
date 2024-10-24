#include <iostream>
#include <string>

using namespace std;

int main () {
    string phrase1;
    string phrase2;

    cout << "Hello! Welcome to search, find and output!!" << endl;

    cout << "\nInput your first phrase: ";
    getline(cin, phrase1);
    cout << "You have entered: " << phrase1 << endl;
    cout << "Input your second phrase: ";
    getline(cin, phrase2);
    cout << "You have entered: " << phrase2 << "\n" << endl;
    
    if (phrase1.find(phrase2) != string::npos) {
        size_t position = phrase1.find(phrase2);
        cout << phrase2 << " is found in " << phrase1 << endl;
        cout << phrase1.substr(position) << endl;
    }
    else if (phrase2.find(phrase1) != string::npos) {
        size_t position = phrase2.find(phrase1);
        cout << phrase1 << " is found in " << phrase2 << endl;
        cout << phrase2.substr(position) << endl;
    }
    else if (phrase1 == phrase2) {
        cout << "Both phrases match." << endl;
    }
    else {
        cout << "No match." << endl;
    }

    cout << "\nThank you!! Goodbye!" << endl;

    return 0;
}