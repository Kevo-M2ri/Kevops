#include <iostream>
using namespace std;

int main() {
    int num;
    cin >> num;

    while (num > 0) {
        cout << num % 2;
        num = num / 2;
    }
    cout << endl;

    return 0;
}