/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        November 10, 2024
   Assignment:  CS-161A Discussion 6
   Description: This program asks the user to input numbers with repeatedly.
                The programs outputs simple statistics done on the numbers when
                the user enters -1.
   Inputs:      user's integers
   Outputs:     sum, average, the number of digits entered, maximum, minimum
   -----------------------------------------------------------------------****/

#include <iostream>
#include <iomanip> 
#include <limits>
#include <cmath>

using namespace std;

int main () {
    // variable declarations
    int nums;
    int count = 0;
    int sum = 0;
    double average = 0.0;
    int maxNum = numeric_limits<int>::min(); // initializing maxNum to the smallest number
    int minNum = numeric_limits<int>::max(); // initializing minNum to the largest number
    double variance = 0.0;
    double standardDeviation = 0.0;

    // Welcome message
    cout << "Hello there!! Welcome to our simple statistics analysis  program!\n" << endl;

    // while
    while (true){
        cout << "Enter a number. (Enter a negative number to quit!): "; // user input prompt
        cin >> nums;

        // condition to quit
        if (nums < 0) {
            break;
        }

        // calculations
        ++count;
        sum += nums;
        average = static_cast<double>(sum) / count;
        if (nums > maxNum) {
            maxNum = nums;
        }
        if (nums < minNum) {
            minNum = nums;
        }
        variance += (nums - average) * (nums - average) / count;
        standardDeviation = sqrt(variance / count);
    }

    // output messages
    cout << fixed << setprecision(2); // set doubles to 2 decimal places
    cout << "\nYou entered: " << count << " digits" << endl;
    cout << "The sum of the numbers is: " << sum << endl;
    cout << "The average is: " << average << endl;
    cout << "The largest number is: " << maxNum << endl;
    cout << "The smallest number is: " << minNum << endl;
    cout << "The standard deviation is: " << standardDeviation << endl;

    // goodbye message
    cout <<"\nGoodbye!! Thank you for using our program!!" << endl;

    return 0;
}