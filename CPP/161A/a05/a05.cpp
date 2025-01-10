/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        October 23, 2024
   Assignment:  CS-161A Assignment a05
   Description: This program asks the user to input two phrases, it checks
                whether one phrase is in the other, outputs the phrase that is
                in the other, and outputs the phrase containing the other from
                the contained phrase. If the phrases are the same, it outputs
                Both phrases match. If non matches the other, it outputs No
                matches.
   Inputs:      phrase1 and phrase2 as strings
   Outputs:     phrasex is in phrasey, No matches, Both phrases match
   -----------------------------------------------------------------------****/

#include <iostream>
#include <string>

using namespace std;

// function main
int main () {
    // variable declaration
    string phrase1;
    string phrase2;

    // welcome message
    cout << "Hello! Welcome to search, find and output!!" << endl;

    // inputs
    cout << "\nInput your first phrase: ";
    getline(cin, phrase1);
    cout << "You have entered: " << phrase1 << endl;
    cout << "Input your second phrase: ";
    getline(cin, phrase2);
    cout << "You have entered: " << phrase2 << "\n" << endl;

    // condition
    if (phrase1 != phrase2){
        // is phrase2 in phrase1?
        if (phrase1.find(phrase2) != string::npos) {
            size_t pos = phrase1.find(phrase2);
            cout << phrase2 << " is found in " << phrase1 << endl;
            cout << phrase1.substr(pos) << endl;
        }
        // is phrase1 in phrase2?
        else if (phrase2.find(phrase1) != string::npos) {
            size_t pos = phrase2.find(phrase1);
            cout << phrase1 << " is found in " << phrase2 << endl;
            cout << phrase2.substr(pos) << endl;
        }
        else {
            cout << "No match." << endl;
        }
    }
    else {
        cout << "Both phrases match." << endl;
    }

    // goodbye message
    cout << "\nThank you!! Goodbye!" << endl;

    return 0;
}