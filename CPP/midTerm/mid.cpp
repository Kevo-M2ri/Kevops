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

int main () {
    string contestant1;
    string contestant2;
    string contestant3;
    int numRocks;
    string contestant;

    cout << "Input the first contestant's name: ";
    getline (cin, contestant1);
    cout << "Input the second contestant's name: ";
    getline (cin, contestant2);
    cout << "Input the third contestant's name: ";
    getline (cin, contestant3);

    return 0;
}