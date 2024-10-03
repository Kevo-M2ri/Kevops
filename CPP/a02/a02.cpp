#include <iostream>
#include <iomanip>

using namespace std;

int main() {
    // variables' declarations
    int idNum = 0;
    int numHrsWorked = 0;
    double hourlyRate = 0;
    double fedWholdRate = 0.15;
    const double FICADEDUCT = 0.0765;
    double grossPay = 0;
    double ficaDedux = 0;
    double fedTaxWhold = 0;
    double totalDedux = 0;
    double netPay = 0;

    // inputs
    cout << "Enter the employee ID number: ";
    cin >> idNum;
    cout << "Enter the number of hours worked: ";
    cin >> numHrsWorked;
    cout << "Enter the hourly rate: ";
    cin >> hourlyRate;

    // calculations
    grossPay = numHrsWorked * hourlyRate;
    ficaDedux = FICADEDUCT * grossPay;
    fedTaxWhold = fedWholdRate * grossPay;
    totalDedux = ficaDedux + fedTaxWhold;
    netPay = grossPay - totalDedux;

    // outputs to the user
    cout << fixed << setprecision(2) << grossPay << endl;
    cout << ficaDedux << endl;
    cout << fedTaxWhold << endl;
    cout << totalDedux << endl;
    cout << netPay << endl;

    return 0;
}