/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        October 6, 2024
   Assignment:  CS-161A Discussion2
   Description: This program calculates and outputs the total cost of gas for
                driving 20, 75, and 500 miles.
   Inputs:      carMpg, and gasPricePerGallon as doubles
   Outputs:     totalGasCost as double for 20, 75, and 500 miles formatted to
                2 decimal places
   -----------------------------------------------------------------------****/

#include <iostream>
#include <iomanip>

using namespace std;

int main(){
    // banner
    cout << "Welcome to my gas price calculator!" << endl;

    // declarations
    double carMpg = 0;
    double gasUsed = 0;
    double gasPricePGallon = 0;
    double totalGasCost = 0;

    // inputs
    cout << "\nEnter your car\'s miles per gallon (MPG): ";
    cin >> carMpg;
    cout << "Enter current gas price per gallon: $";
    cin >> gasPricePGallon;

    // cost for 20 miles
    gasUsed = 20 / carMpg;
    totalGasCost = gasUsed * gasPricePGallon;
    cout << "\nThe gas cost for driving 20 miles is: $" << fixed << setprecision(2) << totalGasCost << endl;

    // cost for 75 miles
    gasUsed = 75 / carMpg;
    totalGasCost = gasUsed * gasPricePGallon;
    cout << "The gas cost for driving 75 miles is: $" << totalGasCost << endl;

    // cost for 500 miles
    gasUsed = 500 / carMpg;
    totalGasCost =  gasUsed * gasPricePGallon;
    cout << "The gas cost for driving 500 miles is: $" << totalGasCost << endl;

    //goodbye
    cout << "\nThank you. Goodbye!" << endl;

    return 0;
}