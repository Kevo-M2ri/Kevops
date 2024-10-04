/**----------------------------------------------------------------------------
   Author:        Kelvin Muturi
   Date:        Octiber 6, 2024
   Assignment:  CS161A Assignment a02
   Description: This program reads the federal Withholding rate, FICA deduction
                percentage
   Inputs:      Employee ID number(integer), Number of hours worked(integer),
                and hourly rate(double)
   Outputs:     gross pay, FICA deduction, federal tax withholding, total
                deduction, and net pay (all as doubles)
   -----------------------------------------------------------------------****/

#include <iostream>
#include <iomanip> //input and output manipulation library

using namespace std;
// function main
int main() {
    // variables' declarations
    int empIdNum = 0;
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
    cin >> empIdNum;
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
    cout << "Your payroll summary:" << endl;
    cout << "Gross amount paid is: " << fixed << setprecision(2) << grossPay << endl; // setting output to 2 decimal places
    cout << "FICA deduction is: " << ficaDedux << endl;
    cout << "Federal Tax Withholding is: " << fedTaxWhold << endl;
    cout << "Total deductions: " << totalDedux << endl;
    cout << "Net Pay is: " << netPay << endl;

    return 0;
}