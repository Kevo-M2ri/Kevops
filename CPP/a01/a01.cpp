/* This program calculates the amount of Pizza required for a pizza party
 * and the total cost of the required pizza
*/

#include <iostream>

using namespace std;

int main() {
    cout << "Welcome to my pizza party Calculator!" << endl;

    int numPeople;
    int pizzas;
    int slicesPerPizza = 12;
    int slicesPerPerson = 2;
    double price = 14.95;
    double cost;
    
    cout << "Enter the number of people attending: ";
    cin >> numPeople;

    pizzas = ((numPeople * slicesPerPerson) / slicesPerPizza);
    cost = price * pizzas;

    cout << "You will need: " << pizzas << " Pizzas." << endl;
    cout << "The total cost is: $" << cost << endl;

    return 0;
}