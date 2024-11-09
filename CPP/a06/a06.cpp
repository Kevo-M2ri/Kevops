/****--------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        November 7, 2024
   Assignment:  CS-161A Assignment a06
   Description: This program asks the user to input the number of attendees,
                average number of slices per person and the cost of a pizza. It
                then calculates and outputs the number of pizzas needed, sales
                tax, delivery fee and the total cost of pizzas. The program
                loops over until the user inputs any other letter (except y/Y)
                at which it outputs the number of parties, total pizzas
                required for all parties, average number of pizzas per party,
                maximum number of people per party, and the maximum cost of the
                parties
   Inputs:      number of attendees, average number of slices per person as
                integers, and cost of a pizza as a double
   Outputs:     number of Pizzas, number of parties, number of Pizzas for
                all the parties, and maximum number of people of the parties as
                integers. Cost of purchasing pizzas in the given party, sales
                tax, delivery fee, total cost of the given party, average
                pizzas per party, maximum cost from the parties as doubles
   -----------------------------------------------------------------------****/

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// constants declaration
const int SLICES_PER_PIZZA = 8;
const double SALES_TAX_PORTION = 0.07;
const double DELIVERY_PORTION = 0.20;

// main
int main () {
    // variables declarations
    int numAttendees = 0;
    double slicesPerPerson = 0;
    double costOfPizza = 0.0;
    char choice;
    int numPizzas = 0;
    double purchaseCost = 0.0;
    double salesTax = 0.0;
    double deliveryFee = 0.0;
    double totalCost = 0.0;
    int count = 0;
    int allPizzas = 0;
    double averAllPizzas = 0.0;
    int maxNumPeople = 0;
    double maxCost = 0.0;

    // welcome message
    cout << "Hello there!! Welcome to Pizza Parties Analysis!!" << endl;

    // do statements
    do {
        // user input prompt
        cout << "\nEnter the number of people in attendance, the average number of slices one person eats, and the cost of one pizza: ";
        cin >> numAttendees >> slicesPerPerson >> costOfPizza;

        // calculations
        numPizzas = ceil(numAttendees * slicesPerPerson / SLICES_PER_PIZZA);
        purchaseCost = costOfPizza * numPizzas;
        salesTax = purchaseCost * SALES_TAX_PORTION;
        deliveryFee = (purchaseCost + salesTax) * DELIVERY_PORTION;
        totalCost = purchaseCost + salesTax + deliveryFee;

        // outputs an formatting
        cout << fixed << setprecision(2) << endl; // decimal places formating
        cout << "Number of Pizzas needed: ";
        cout << numPizzas << endl;
        cout << "Cost of all Pizzas: ";
        cout << setw(5) << right << "$" << purchaseCost << endl;
        cout << "Tax: ";
        cout << setw(20) << right << "$" << salesTax << endl;
        cout << "Delivery Fee: ";
        cout << setw(11) << right << "$" << deliveryFee << endl;
        cout << "Total cost: $";
        cout << setw(12) << right << "$" << totalCost << endl;

        // statistics data collection and manipulation
        ++count;
        allPizzas += numPizzas;
        averAllPizzas = static_cast<double>(allPizzas) / count;
        // highest number of people condition
        if (numAttendees > maxNumPeople) {
            maxNumPeople = numAttendees;
        }
        // greatest cost incurred
        if (totalCost > maxCost) {
            maxCost = totalCost;
        }

        // loop prompt
        cout << "\nDo you want to enter more (Input y to continue. any other input to quit): ";
        cin >> choice;

    }
    while ((choice == 'y') || (choice == 'Y')); // while condition

    // outputs
    cout << "\nNumber of parties: " << count << endl;
    cout << "Total Number of Pizzas: " << allPizzas << endl;
    cout << fixed << setprecision(1) << "Average number of pizzas: " << averAllPizzas << endl;
    cout << "Maximum number of people: " << maxNumPeople << endl;
    cout << fixed << setprecision(2) << "Maximum cost of pizzas: $" << maxCost << endl;

    // termination message
    cout << "\nThank you for using my Calculator!! Goodbye!" << endl;

    return 0;
} // end main
