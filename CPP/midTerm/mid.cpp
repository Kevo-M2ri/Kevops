/****--------------------------------------------------------------------------
   Author:      November 1, 2024
   Assignment:  CS-161A Midterm
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
#

using namespace std;

int main () {
    string contestant1;
    string contestant2;
    string contestant3;
    int numRocks;
    string contestant;
    int numRocks1;
    int numRocks2;
    int numRocks3;
    string first;
    string second;
    string third;

    cout << "Hello!! Welcome to the winners program!!" << endl;

    cout << "Input the first contestant's name: ";
    getline (cin, contestant1);
    cout << "Input the second contestant's name: ";
    getline (cin, contestant2);
    cout << "Input the third contestant's name: ";
    getline (cin, contestant3);

    cout << "Input what " << contestant1 << " has: ";
    cin >> numRocks1;
    cout <<"Input what " << contestant2 << " has: ";
    cin >> numRocks2;
    cout << "Input what " << contestant3 << " has: ";
    cin >> numRocks3;

    if ((numRocks1 < 0) || (numRocks2 < 0) || (numRocks3 < 0)) {
        cout << "Error!! Number of Rocks cannot be negative!!";
        numRocks = 0;
    }
    else {
        if ((numRocks1 == numRocks2) && (numRocks2 == numRocks3)) {
            first = contestant1.append(", ").append(contestant2).append(", and ").append(contestant3);
        }
        else {
            if ((numRocks1 != numRocks2) && (numRocks2 != numRocks3)) {
                if ((numRocks1 > numRocks2) && (numRocks2 > numRocks3)) {
                    first = contestant1;
                    second = contestant2;
                    third = contestant3;
                }
                else if ((numRocks2 > numRocks1) && (numRocks1 > numRocks3)) {
                    first = contestant2;
                    second = contestant1;
                    third = contestant3;
                }
                else if ((numRocks1 > numRocks3) && (numRocks3 > numRocks2)) {
                    first = contestant1;
                    second = contestant3;
                    third = contestant2;
                }
            }
        }
    }

    if ((numRocks1 != numRocks2) && (numRocks1 != numRocks3) && (numRocks2 != numRocks3)) {
        cout << "The first winner is: " << first << endl;
        cout << "The second winner is: " << second << endl;
        cout << "The third winner is: " << third << endl;
    }
    else {
        if ((numRocks1 == numRocks2) && (numRocks2 == numRocks3)) {
            cout << "It\'s a tie! All are winners!" << endl;
            cout << "The names are: " << first << endl;
        }
    }
        

    return 0;
}