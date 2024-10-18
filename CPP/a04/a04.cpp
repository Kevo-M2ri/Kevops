/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        October 17, 2024
   Assignment:  CS-161A Assignment a04
   Description: This program shows the menu of product prices in a Ferry,
                calculates and outputs the cost of an individual or a group of
                less than 20 people, and gives a discount for next Ferry trip
                for one adult if the price payed is $100 or more and offers
                the remaining balance from obtaining a free ticket if bill is
                less than 100.
   Inputs:      response as a character. numBikes, numAdults, numSeniors,
                numYouths as integers
   Outputs:     menu as a string, totalCharge as a double
   -----------------------------------------------------------------------****/

#include <iostream>
#include <iomanip>

using namespace std;

// constants declaration
const double VEHICLE_CHARGE = 57.90;
const double ADULT_CHARGE = 14.95;
const double SENIOR_CHARGE = 7.40;
const double YOUTH_CHARGE = 5.55;
const double BIKE_SURCHARGE = 4.00;

int main () {
    // variables declaration
    char response;
    int numBikes = 0;
    int numAdults = 0;
    int numSeniors = 0;
    int numYouths = 0;
    int allPeople = 0;
    double totalCharge = 0.0;

    // Welcome message
    cout << "Welcome to Washington State Ferries." << endl;
    cout << "Here is our Ferries' fare MENU" << endl << endl;

    //menu header
    cout << setw(40) << left << "Fare Description";
    cout << setw(30) << right << "Tickets ($)" << endl;

    // menu header/body separation
    cout << setfill('-') << setw(43) << left << "";
    cout << setfill(' ') << setw(16) << right << "";
    cout << setfill('-') << setw(11) << right << "" << endl;

    cout << setfill(' ');

    // menu body
    cout << fixed << setprecision(2);
    cout << setw(40) << left << "Vehicle Under 14\' (less than 168\") & Driver";
    cout << setw(27) << right << VEHICLE_CHARGE << endl;
    cout << setw(40) << left << "Adult (ages 19 - 64)";
    cout << setw(30) << right << ADULT_CHARGE << endl;
    cout << setw(40) << left << "Senior (ages 65 & over)";
    cout << setw(30) << right << SENIOR_CHARGE << endl;
    cout << setw(40) << left << "Youth (ages 6 - 18)";
    cout << setw(30) << right << YOUTH_CHARGE << endl;
    cout << setw(40) << left << "Bicycle Surcharge (included with Vehicle)";
    cout << setw(29) << right << BIKE_SURCHARGE << endl << endl;

    // inquiry_1
    cout << "Are you riding a vehicle on the Ferry (Y/N)? ";
    cin >> response;

    // if branch_1
    if (response == 'Y' || response == 'y' || response == 'N' || response == 'n') {
        cout << "\nHow many adults? ";
        cin >> numAdults;
        cout << "How many seniors? ";
        cin >> numSeniors;
        cout << "How many youths? ";
        cin >> numYouths;

        allPeople = numAdults + numSeniors + numYouths;

        // if branch_2
        if (allPeople > 20) {
            cout << "\nUh oh!! Too many people in your group. Split into groups of at most 20 people and try again!"<< endl;
        }
        else {
            // if branch_3
            if (numAdults < 0 || numSeniors < 0 || numYouths < 0){
                cout << "ERROR! Only positive numbers are allowed. Try again later!" << endl;
            }
            else {
                // if branch_4.1
                if (response == 'Y' || response == 'y') {
                    numBikes = 0;
                }
                else if (response == 'N' || response == 'n') {
                    cout << "How many bikes? ";
                    cin >> numBikes;
                }

                totalCharge = VEHICLE_CHARGE + (ADULT_CHARGE * numAdults) + (SENIOR_CHARGE * numSeniors) + (YOUTH_CHARGE * numYouths) + (numBikes * BIKE_SURCHARGE);
                cout << "\nYour total charge is: $" << totalCharge << endl << endl;

                //if branch_4.2
                if (totalCharge >= 100) {
                    cout << "Congratulations! You have obtained a free adult ticket for your next trip."<< endl;
                }
                else {
                    cout << "Spend $" << 100 - totalCharge << " more and get a FREE adult ticket for your next trip." << endl;
                }
            }
        }
    }
    else {
        cout << "\nError!! Invalid answer!! You can only key in (y/n)!! Please try again later!!!" << endl;
    }

    // goodbye message
    cout << "\nThank you. Goodbye!" << endl;

    return 0;
}