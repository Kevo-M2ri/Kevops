/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        November 2, 2024
   Assignment:  CS-161A Midterm
   Description: This program asks the user to input three names of contestants,
                and the respective number of rocks each contestant has
                collected. It then ranks the contestants according to the number
                of rocks each has collected, lists them from the one with the
                most to the one with the least. It the calculates and outputs
                the average number of rocks collected as a double
   Inputs:      contestant1, contestant2, and contestant3 as strings, and
                numRocks1, numRocks2, and numRocks3 as integers
   Outputs:     contestant1, contestant2, and contestant3 in order of one with
                the most rocks to the one with the least, as strings, and
                average number of rocks collected as a double
   -----------------------------------------------------------------------****/

#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

//constant declaration
const int NUM_PLAYERS = 3;

int main () {
    //variables declaration
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

    // welcome message
    cout << "Hello!! Welcome to the winners program!!" << endl;

    // contestants input prompt
    cout << "\nInput the first contestant's name: ";
    getline (cin, contestant1);
    cout << "Input the second contestant's name: ";
    getline (cin, contestant2);
    cout << "Input the third contestant's name: ";
    getline (cin, contestant3);

    // number of rocks each contestant collects input prompt
    cout << "\nInput what " << contestant1 << " has: ";
    cin >> numRocks1;
    cout <<"Input what " << contestant2 << " has: ";
    cin >> numRocks2;
    cout << "Input what " << contestant3 << " has: ";
    cin >> numRocks3;

    // valid numbers for number of rocks
    if ((numRocks1 < 0) || (numRocks2 < 0) || (numRocks3 < 0)) {
        if ((numRocks = numRocks1) || (numRocks = numRocks2) || (numRocks = numRocks3)) {
            // error message output and assigning
            cout << "Error!! Number of Rocks can only be at least!! try again!!" << endl;
            numRocks = 0;
        }
    }
    else {
        // equal number of rocks for all
        if ((numRocks1 == numRocks2) && (numRocks2 == numRocks3)) {
            first = contestant1.append(", ").append(contestant2).append(", and ").append(contestant3); // listing all names
        }
        else {
            // unequal number of rocks
            if ((numRocks1 != numRocks2) && (numRocks2 != numRocks3)) {
                // obtaining largest to smallest
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
            // two contestants having equal number of rocks
            else if (numRocks1 == numRocks2) {
                // obtaining the one(s) with the highest number of rocks
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
        // output conditions
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

        // average number of rocks collected
        average = static_cast<double>(numRocks1 + numRocks2 + numRocks3) / NUM_PLAYERS;

        cout << fixed << setprecision(2); // setting output to 2 decimal places
        cout << "\nThe average number of rocks collected is: " << average << endl;
    }

    // goodbye message
    cout << "\nThank you! Have a good one!" << endl;

    return 0;
}