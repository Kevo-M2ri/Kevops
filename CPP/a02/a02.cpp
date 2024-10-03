#include <iostream>
#include <iomanip> //input and output manipulation library

using namespace std;
// function main
int main() {
    // variables' declarations
    int idNum = 0;
    int numHrsWorked = 0;
    double hourlyRate = 0;
    double fedWholdRate = 0.15;
    const double FICADEDUCT = 0.0765; //constant declaration
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
    cout << "Your payroll summary is:" << endl;
    cout << "Gross amount payed is: " << fixed << setprecision(2) << grossPay << endl; // setting output to 2 decimal places
    cout << "FICA deduction is: " << ficaDedux << endl;
    cout << "Federal Tax Withholding is: " << fedTaxWhold << endl;
    cout << "Total deductions: " << totalDedux << endl;
    cout << "Net Pay is: " << netPay << endl;

    return 0;
}