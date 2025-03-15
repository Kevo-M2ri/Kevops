/******************************************************************************
# Author:           Kelvin Muturi
# Lab:              Discussion #6
# Date:             March 14, 2025
# Description:      This program asks the user to enter the make, model, year,
                    price, and mileage of a car. It then stores this information
                    in a structure and displays it to the user. 
# Input:            car.make, car.model as character arrays and car.year as an
                    integer, car.price, car.mileage as doubles
# Output:           car.make, car.model as character arrays and car.year as an
                    integer, car.price, car.mileage as doubles
# Sources:          
#******************************************************************************/
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX = 25;// max size of array
// structure to hold car details
struct Car{
    char make[MAX];
    char model[MAX];
    int year;
    double price;
    double mileage;
};
// function prototypes
void welcome();
void getCarDetails(Car &car);
void printCarDetails(const Car &car);
void goodbye();

// main function
int main() {
    Car car;// declare car structure variable

    welcome();// welcome function
    getCarDetails(car);// get car details function
    cout << endl; // output blank line
    printCarDetails(car);// print car details function
    goodbye();// goodbye function

    return 0;
}

// function to display welcome message
void welcome() {
    cout << "Welcome to the car database!" << endl;
    cout << "Please enter the following information about the car." << endl;
    cout << endl;
}

// function to get car details from user
void getCarDetails(Car &car) {
    cout << "Enter the make of the car: ";
    cin.getline(car.make, MAX);
    cout << "Enter the model of the car: ";
    cin.getline(car.model, MAX);

    cout << "Enter the year of the car: ";
    while(!(cin >> car.year) || car.year < 1986 || car.year > 2026) {
        cout << "Invalid input. Please enter a valid year: (1986-2026) ";
        cin.clear();
        cin.ignore(100, '\n');
    } // check for valid year, if not valid, prompt user to try again

    cout << "Enter the price of the car: ";
    while (!(cin >> car.price) || car.price < 0.0) {
        cout << "Invalid input. Please enter a valid price: ";
        cin.clear();
        cin.ignore(100, '\n');
    }// check for valid price, if not valid, prompt user to try again

    cout << "Enter the mileage of the car: ";
    while (!(cin >> car.mileage) || car.mileage < 0.0) {
        cout << "Invalid input. Please enter valid mileage: ";
        cin.clear();
        cin.ignore(100, '\n');
    } // check for valid mileage, if not valid, prompt user to try again
    cin.ignore(); // clear the input buffer
}

//function to print car details
void printCarDetails(const Car &car) {
    cout << left << setw(10) << "Make: " << car.make << endl;
    cout << left << setw(10) << "Model: " << car.model << endl;
    cout << left << setw(10) << "Year: " << car.year << endl;
    cout << left << setw(10) << "Price: " << car.price << endl;
    cout << left << setw(10) << "Mileage: " << car.mileage << endl;
}

// function to display goodbye message
void goodbye() {
    cout << endl;
    cout << "Thank you for using the car database!" << endl;
}