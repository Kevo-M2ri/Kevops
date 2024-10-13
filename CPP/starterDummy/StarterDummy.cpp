#include <iostream>

using namespace std;

int main () {
    int highwayNumber;

    cin >> highwayNumber;

    if ((highwayNumber > 0) && (highwayNumber <= 99)) {
        if ((highwayNumber % 2 == 0) && (highwayNumber % 5 == 0)) {
             cout << "I-" << highwayNumber << " is primary, going east/west.";
        }
        else if (highwayNumber % 5 == 0) {
            cout << "I-" << highwayNumber << " is primary, going north/south.";
        }
    }
    
    else if ((highwayNumber > 100) && (highwayNumber <= 999)) {
        if (highwayNumber % 100 == 0) {
            cout << highwayNumber << " is not a valid interstate highway number.";
        }
        else if ((highwayNumber % 2 == 0) && (highwayNumber % 5 == 0)) {
            cout << "I-" << highwayNumber << " is auxiliary, serving I-" << highwayNumber % 100 << ", going east/west.";
        }
        else if (highwayNumber % 5 == 0) {
            cout << "I-" << highwayNumber << " is auxiliary, serving I-" << highwayNumber % 100 << ", going north/south.";
        }
    }

    else {
        cout << highwayNumber << " is not a valid interstate highway number.";
    }
    cout << endl;

    return 0;
}