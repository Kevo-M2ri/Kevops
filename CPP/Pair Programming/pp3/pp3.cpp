/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        November 10, 2024
   Assignment:  CS-161A Discussion 6
   Description: This program asks the user for 
   Inputs:      
   Outputs:     
   -----------------------------------------------------------------------****/

#include <iostream>
#include <iomanip> 
#include <limits>

using namespace std;

int main () {
    int nums;
    int count = 0;
    int sum = 0;
    double average = 0.0;
    int maxNum = numeric_limits<int>::min();
    int minNum = numeric_limits<int>::max();

    cout << "Hello there!! Welcome to our simple statistics analysis  program!\n" << endl;

    while (true){
        cout << "Enter a number. (Enter -1 to quit!): ";
        cin >> nums;

        if (nums == -1) {
            break;
        }
        ++count;
        sum += nums;
        average = static_cast<double>(sum) / count;
        if (nums > maxNum) {
            maxNum = nums;
        }
        if (nums < minNum) {
            minNum = nums;
        }
    }

    cout << fixed << setprecision(2);
    cout << "\nYou entered: " << count << " digits" << endl;
    cout << "The sum of the numbers is: " << sum << endl;
    cout << "The average is: " << average << endl;
    cout << "The largest number is: " << maxNum << endl;
    cout << "The smallest number is: " << minNum << endl;

    cout <<"\nGoodbye!! Thank you for using our program!!" << endl;

    return 0;
}