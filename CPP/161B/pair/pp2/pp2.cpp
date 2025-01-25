#include <iostream>
#include <limits>
using namespace std;

void welcome();
void readInput(int array[], int numVals, int &pos);
void checkArray(int Array[]);

const int MAXINPUT = 20;

int main() { //function main
    int array[MAXINPUT];
    int numVals;
    int pos;

    welcome();
    readInput(array, numVals, pos);

    return 0;
}

void welcome() {
    cout << "Hello!" << endl;
}

void readInput(int array[], int numVals, int &pos) {
    cout << "Input the number of items to be taken by the array(Must be between 1 and " << MAXINPUT << "): ";
    cin >> numVals;
    while (cin.fail() || numVals <= 0 || numVals > MAXINPUT) {
        cin.clear(); 
        cin.ignore(numeric_limits<streamsize> ::max(), '\n');
        cout << "Error!!! Input out of range!! Please input value between 1 and " << MAXINPUT << "!" << endl;
        cin >> numVals;
    } //numVals is a number within the accepatable range

    for (pos = 0; pos < numVals; pos++) {
        cout << "Input the items in the array(Must count to " << numVals << "): ";
        cin >> array[pos];
        while(cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Not a unit of the input! Try again." << endl;
            cin >> array[pos];
        }   
    } 
}

void checkArray(int array[]) {
    int numVals;
    int pos;
    readInput(array, numVals, pos);

    for (pos = 0; pos < numVals; pos++) {
        array[pos];
    }
}