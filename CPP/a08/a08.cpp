#include <iostream>

using namespace std;

void Welcome();
int ReadInt(string prompt);

int main () {
    Welcome();
    return 0;
}

void Welcome() {
    int numAssignments;
    cout << "Hello!! Welcome to the grade calculator!" << endl;

    numAssignments = ReadInt("Input the number of assignments");
}

int ReadInt (string prompt) {
    int assignments;
    cin >> assignments;

    return assignments;
}