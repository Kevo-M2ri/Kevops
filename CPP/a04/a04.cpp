#include <iostream>
#include <iomanip>

using namespace std;

const double VEHICLE_CHARGE = 57.90;
const double ADULT_CHARGE = 14.95;
const double SENIOR_CHARGE = 7.40;
const double YOUTH_CHARGE = 5.55;
const double BIKE_SURCHARGE = 4.00;

int main () {
    cout << "Welcome to Washington State Ferries." << endl;
    cout << "Here is our Ferries' fare MENU" << endl << endl;

    cout << setw(40) << left << "Fare Description";
    cout << setw(30) << right << "Tickets ($)" << endl;

    cout << setfill('-') << setw(43) << left << "";
    cout << setfill(' ') << setw(16) << right << "";
    cout << setfill('-') << setw(11) << right << "" << endl;

    cout << setfill(' ');

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

    char response;
    int numBikes = 0;
    int numAdults = 0;
    int numSeniors = 0;
    int numYouths = 0;
    int allPeople = 0;
    double totalCharge = 0.0;


    cout << "Are you riding a vehicle on the Ferry (Y/N)? ";
    cin >> response;

    if (response == 'Y' || response == 'y' || response == 'N' || response == 'n') {
        cout << "\nHow many adults? ";
        cin >> numAdults;
        cout << "How many seniors? ";
        cin >> numSeniors;
        cout << "How many youths? ";
        cin >> numYouths;

        allPeople = numAdults + numSeniors + numYouths;

        if (allPeople > 20) {
            cout << "\nUh oh!! Too many people in your group. Split into groups of at most 20 people and try again!"<< endl;
        }
        else {
            if (numAdults < 0 || numSeniors < 0 || numYouths < 0){
                cout << "ERROR! Only positive numbers are allowed. Try again later!" << endl;
            }
            else {
                if (response == 'Y' || response == 'y') {
                    numBikes = 0;
                }
                else if (response == 'N' || response == 'n') {
                    cout << "How many bikes? ";
                    cin >> numBikes;
                }

                totalCharge = VEHICLE_CHARGE + (ADULT_CHARGE * numAdults) + (SENIOR_CHARGE * numSeniors) + (YOUTH_CHARGE * numYouths) + (numBikes * BIKE_SURCHARGE);
                cout << "\nYour total charge is: $" << totalCharge << endl << endl;
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

    cout << "\nThank you. Goodbye!" << endl;

    return 0;
}