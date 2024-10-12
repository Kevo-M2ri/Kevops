/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        October 9, 2024
   Assignment:  CS-161A Assignment a03
   Description: This program calculates and outputs the number of servings for
                cookies eaten and the total calories taken in rounded to one
                decimal place.
   Inputs:      Number of cookies eaten as an integer
   Outputs:     Number of servings and the total calories taken in as doubles
   -----------------------------------------------------------------------****/

#include <iostream>
#include <iomanip> // input and output manipulation library

using namespace std;

// constants declaration
const int NUM_COOKIES_P_SERVING = 5;
const int CALORIES_P_SERVING = 160;

int main(){
    // welcome message
    cout << "Welcome to our calories' calculator!\n";
    cout << "Note one serving is 5 cookies. One serving has 160 calories." << endl;

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