#include <iostream>
#include <math.h>
#include "Car.h"
using namespace std;

//default constructor
Car::Car()
{
   modelYear = 0;
   purchasePrice = 0;
   currentValue = 0;
}

//setter for modelYear
void Car::SetModelYear(int userYear){
   modelYear = userYear;
}

//getter for modelYear
int Car::GetModelYear() const {
   return modelYear;
}

//setter for purchasePrice
void Car::SetPurchasePrice(int userPrice){
   purchasePrice = userPrice;
}

int Car::GetPurchasePrice() const {
   return purchasePrice;
}

void Car::CalcCurrentValue(int currentYear) {
   double depreciationRate = 0.15;
   int carAge = currentYear - modelYear;
      
   // Car depreciation formula
   currentValue = (int) 
      round(purchasePrice * pow((1 - depreciationRate), carAge));
}

void Car::PrintInfo() const {
   cout << "Car's information:" << endl;
   cout << "  Model year: " << modelYear << endl;
   cout << "  Purchase price: $" << purchasePrice << endl;
   cout << "  Current value: $" << currentValue << endl;
}