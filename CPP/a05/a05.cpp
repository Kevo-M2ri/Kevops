#include <iostream>
#include <string>

using namespace std;

int main () {
    string phrase1;
    string phrase2;
    bool present = false;

    cout << "Input your first phrase: ";
    cin >> phrase1;
    cout << "You have entered: " << phrase1 << endl;
    cout << "Input your second phrase: ";
    cin >> phrase2;
    cout << "You have entered: " << phrase2 << endl;
    
    if (present != phrase1.find(phrase2)) {
        cout << phrase1 << " is found in " << phrase2 << endl;
    }

    else if (present != phrase2.find(phrase1)) {
        cout << phrase2 << " is found in " << phrase1 << endl;
    }
    else if ((present != phrase1.find(phrase2)) && (present != phrase2.find(phrase1))) {
        cout << "Both phrases match." << endl;
    }
    else {
        cout << "No match." << endl;
    }

    return 0;
}