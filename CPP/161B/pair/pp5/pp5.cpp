#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX = 25;

struct Car
{
    char make[MAX];
    char model[MAX];
    int year;
    double price;
    double mileage;
};

void welcome();
void getCarDetails(Car &car);
void printCarDetails(const Car &car);
void goodbye();

int main() {
    Car car;

    welcome();
    getCarDetails(car);
    cout << endl;
    printCarDetails(car);
    goodbye();

    return 0;
}
void welcome() {
    cout << "Welcome to the car database!" << endl;
    cout << "Please enter the following information about the car." << endl;
    cout << endl;
}

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
    }

    cout << "Enter the price of the car: ";
    while (!(cin >> car.price) || car.price < 0) {
        cout << "Invalid input. Please enter a valid price: ";
        cin.clear();
        cin.ignore(100, '\n');
    }

    cout << "Enter the mileage of the car: ";
    while (!(cin >> car.mileage) || car.mileage < 0) {
        cout << "Invalid input. Please enter a valid mileage: ";
        cin.clear();
        cin.ignore(100, '\n');
    }
    cin.ignore();
}

void printCarDetails(const Car &car) {
    cout << left << setw(10) << "Make: " << car.make << endl;
    cout << left << setw(10) << "Model: " << car.model << endl;
    cout << left << setw(10) << "Year: " << car.year << endl;
    cout << left << setw(10) << "Price: " << car.price << endl;
    cout << left << setw(10) << "Mileage: " << car.mileage << endl;
}

void goodbye() {
    cout << endl;
    cout << "Thank you for using the car database!" << endl;
}