/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        November 1, 2024
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

const int NUM_PLAYERS = 3;

int main () {
    string contestant1;
    string contestant2;
    string contestant3;
    int numRocks;
    int numRocks1;
    int numRocks2;
    int numRocks3;
    string first;
    string second;
    string third;
    double average;

    cout << "Hello!! Welcome to the winners program!!" << endl;

    cout << "\nInput the first contestant's name: ";
    getline (cin, contestant1);
    cout << "Input the second contestant's name: ";
    getline (cin, contestant2);
    cout << "Input the third contestant's name: ";
    getline (cin, contestant3);

    cout << "\nInput what " << contestant1 << " has: ";
    cin >> numRocks1;
    cout <<"Input what " << contestant2 << " has: ";
    cin >> numRocks2;
    cout << "Input what " << contestant3 << " has: ";
    cin >> numRocks3;

    if ((numRocks1 < 0) || (numRocks2 < 0) || (numRocks3 < 0)) {
        if ((numRocks = numRocks1) || (numRocks = numRocks2) || (numRocks = numRocks3)) {
            cout << "Error!! Number of Rocks can only be at least!! try again!!" << endl;
            numRocks = 0;
        }
    }
    else {
        if ((numRocks1 == numRocks2) && (numRocks2 == numRocks3)) {
            first = contestant1.append(", ").append(contestant2).append(", and ").append(contestant3);
        }
        else {
            if ((numRocks1 != numRocks2) && (numRocks2 != numRocks3)) {
                if ((numRocks1 > numRocks2) && (numRocks1 > numRocks3)) {
                    first = contestant1;
                    if (numRocks2 > numRocks3) {
                        second = contestant2;
                        third = contestant3;
                    }
                    else {
                        second = contestant3;
                        third = contestant2;
                    }
                }
                else if ((numRocks2 > numRocks1) && (numRocks2 > numRocks3)) {
                    first = contestant2;
                    if (numRocks1 > numRocks3) {
                        second = contestant1;
                        third =  contestant3;
                    }
                    else {
                        second = contestant3;
                        third = contestant1;
                    }
                }
                else if ((numRocks3 > numRocks1) && (numRocks3 > numRocks2)) {
                    first = contestant3;
                    if (numRocks1 > numRocks2) {
                        second = contestant1;
                        third = contestant2;
                    }
                    else {
                        second = contestant2;
                        third = contestant1;
                    }
                }
            }
            else if (numRocks1 == numRocks2) {
                if (numRocks1 > numRocks3) {
                    first = contestant1.append(", and ").append(contestant2);
                    third = contestant3;
                }
                else {
                    first = contestant3;
                    second = contestant1.append(", and ").append(contestant2);
                }
            }
            else if (numRocks1 == numRocks3) {
                if (numRocks1 > numRocks2) {
                    first = contestant1.append(", and ").append(contestant3);
                    third = contestant2;
                }
                else {
                    first = contestant2;
                    second =contestant1.append(", and ").append(contestant3);
                }
            }
            else if (numRocks2 = numRocks3) {
                if (numRocks2 > numRocks1) {
                    first = contestant2.append(", and ").append(contestant3);
                    third = contestant1;
                }
                else {
                    first = contestant1;
                    second = contestant2.append(", and ").append(contestant3);
                }
            }
        }
        if ((numRocks1 != numRocks2) && (numRocks1 != numRocks3) && (numRocks2 != numRocks3)) {
            cout << "\nThe first winner is: " << first << endl;
            cout << "The second winner is: " << second << endl;
            cout << "The third winner is: " << third << endl;
        }
        else {
            if ((numRocks1 == numRocks2) && (numRocks2 == numRocks3)) {
                cout << "\nIt\'s a tie! All are winners!" << endl;
                cout << "The names are: " << first << endl;
            }
            else if ((numRocks1 == numRocks2) && (numRocks1 != numRocks3) && (numRocks2 != numRocks3)) {
                if (numRocks2 > numRocks3) {
                    cout << "\nIt\'s a tie!! The first winners are: " << first << endl;
                    cout << "The third winner is: " << third << endl;
                }
                else {
                    cout << "\nThe first winner is: " << first << endl;
                    cout << "We have a tie! The second winners are: " << second << endl;
                }
            }
            else if ((numRocks1 == numRocks3) && (numRocks1 != numRocks2) && (numRocks3 != numRocks2)) {
                if (numRocks3 > numRocks2) {
                    cout << "\nIt's a tie! The first winners are: " << first << endl;
                    cout << "The third winner is: " << third << endl;
                }
                else {
                    cout << "\nThe first winner is: " << first << endl;
                    cout << "We have a tie! The second winners are: " << second << endl;
                }
            }
            else if ((numRocks2 == numRocks3) && (numRocks2 != numRocks1) && (numRocks3 != numRocks1)) {
                if (numRocks3 > numRocks1) {
                    cout << "\nIt's a tie! The first winners are: " << first << endl;
                    cout << "The third winner is: " << third << endl;
                }
                else {
                    cout << "\nThe first winner is: " << first << endl;
                    cout << "We have a tie! The second winners are: " << second << endl;
                }
            }
        }
    }

    cout << "\nThank you! Have a good one!" << endl;

    return 0;
}