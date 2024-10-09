/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        October 9, 2024
   Assignment:  CS-161A Assignment a03
   Description: This program calculates and outputs the weekly gross salary,
                total deductions and the net salary.
   Inputs:      Employee ID number(integer), Number of hours worked(integer),
                and hourly rate(double).
   Outputs:     gross pay, FICA deduction, federal tax withholding, total
                deduction, and net pay (all as doubles).
   -----------------------------------------------------------------------****/

#include <iostream>
#include <iomanip> // input and output manipulation library

using namespace std;

// constants declaration
const int NUM_COOKIES_P_SERVING = 5;
const int CALORIES_P_SERVING = 160;

int main(){
    // welcome message
    cout << "Welcome to our calories' calculator!" << endl;

    // variable declarations
    int numCookiesEaten;
    double numServings;
    double totalCalories;

    // user input
    cout << "\nInput the number of cookies you have eaten: ";
    cin >> numCookiesEaten;

    // calculations
    numServings = static_cast<double>(numCookiesEaten) / static_cast<double>(NUM_COOKIES_P_SERVING);
    totalCalories = static_cast<double>(CALORIES_P_SERVING) * numServings;

    // output
    cout << "\n" << numCookiesEaten << " cookies are equal to: " << fixed << setprecision(1) << numServings << " servings." << endl;
    cout << "You have taken in: " << totalCalories << " calories." << endl;

    // goodbye message
    cout << "\nKeep choosing Oreo. Enjoy!" << endl;

    return 0;
}