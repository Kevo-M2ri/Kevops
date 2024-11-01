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

    cout << "Input what " << contestant1 << "has: ";
    cin >> numRocks1;
    cout <<"Input what " << contestant2 << "has: ";
    cin >> numRocks2;
    cout << "Input what " << contestant3 << "has: ";
    cin >> numRocks3;

    if (numRocks == numRocks1 || numRocks == numRocks2 || numRocks == numRocks3) {
        if (numRocks < 0) {
            cout << "Error!! Number of Rocks cannot be negative!!";
            numRocks = 0;
        }
        else {
            if ((numRocks1 >= numRocks2) && (numRocks1 >= numRocks3)) {
                if ((numRocks1 > numRocks2) && (numRocks2 > numRocks3)) {
                    first = contestant1;
                    second = contestant2;
                    third = contestant3;
                }

                else if ((numRocks1 == numRocks2) && (numRocks2 > numRocks3)) {
                    first = contestant1 + contestant2;
                    third = contestant3;
                }

                else if ((numRocks1 > numRocks2) && (numRocks2 == numRocks3)) {
                    first = contestant1;
                    second = contestant2 + contestant3;
                }
                else {
                    first = contestant1 + contestant2 + contestant3;
                }

                cout << "The first winner is: " << first << endl;
                if (first == contestant1) {
                    cout << "The second winner is: " << second << endl;
                    if (second == contestant2) {
                        cout << "The third winner is: " << third << endl;
                }
                else if (first == contestant1 + contestant2) {
                    cout << "The third winner is " << third;
                }
            }
            else if ((numRocks2 > numRocks3) && (numRocks2 > numRocks1)) {
                first = contestant2;
                if (numRocks1 > numRocks3) {
                    second = contestant1;
                    third = contestant3;
                }
                else {
                    second = contestant3;
                    third = contestant1;
                }
            }
            else if ((numRocks3 > numRocks1) && (numRocks3 > numRocks2)) {
                first = numRocks3;
                if (numRocks1 > numRocks2) {
                    second = numRocks1;
                    third = numRocks2;
                }
                else {
                    second = numRocks2;
                    third = numRocks1;
                }
            }
        }

    }
    }

    return 0;
}