#include <iostream>
#include <iomanip>
#include <cmath>
#include <limits>

using namespace std;

const int SQUARE_FEET_PER_GALLON = 110;
const double LABOR_HOURS_PER_GALLON = 8.0;
const double LABOR_COST_PER_HOUR = 35.0;


double GetPaintPrice();
void GetWallDimensions(double& length, double& width, double& height);
double CalcWallSquareFeet(double length, double width, double height);
void NumberOfGallons(double squareFeet, int& gallons);
void LaborHours(double squareFeet, int& hours);
void DisplayCost(int gallons, double paintCostPerGallon, int hours);

int main() {

  double length;
  double width;
  double height;
  double paintPricePerGallon;
  double wallSquareFeet;
  int gallonsRequired;
  int laborHoursRequired;
  
  GetWallDimensions(length, width, height);
  paintPricePerGallon = GetPaintPrice();
  wallSquareFeet = CalcWallSquareFeet(length, width, height);
  NumberOfGallons(wallSquareFeet, gallonsRequired);
  LaborHours(wallSquareFeet, laborHoursRequired);
  DisplayCost(gallonsRequired, paintPricePerGallon, laborHoursRequired);

   return 0;
}

double GetPaintPrice() {
   double price;
   bool validInput = false;
   
   do {
      cin >> price;
      
      if (cin.fail() || price < 10.00) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         cout << "ERROR: Paint price must be 10.00 or greater.\n";
      }
      else {
         validInput = true;
      }
   }while (!validInput);
   
   return price;
}

void GetWallDimensions(double& length, double& width, double& height) {
   bool validInput = false;
   
   do {
      cin >> length >> width >> height;
      
      if (cin.fail() || length < 5.0 || width < 5.0 || height < 5.0) {
         cin.clear();
         cin.ignore(numeric_limits<streamsize>::max(), '\n');
         if (length < 5.0) cout << "ERROR: Cannot be less than 5 feet.\n";
         if (width < 5.0) cout << "ERROR: Cannot be less than 5 feet.\n";
         if (height < 5.0) cout << "ERROR: Cannot be less than 5 feet.\n";
      }
      else {
         validInput = true;
      }
   } while (!validInput);
}

double CalcWallSquareFeet(double length, double width, double height) {
   return 2 * (length * height + width * height);
}

void NumberOfGallons(double squareFeet, int& gallons) {
   gallons = ceil(squareFeet / SQUARE_FEET_PER_GALLON);
}

void LaborHours(double squareFeet, int& hours) {
   int gallons;
   
   gallons = ceil(squareFeet / SQUARE_FEET_PER_GALLON);
   hours = ceil(gallons * LABOR_HOURS_PER_GALLON);
}

void DisplayCost(int gallons, double paintCostPerGallon, int hours) {
   double paintCost;
   double laborCost;
   double totalCost;
   
   paintCost = gallons * paintCostPerGallon;
   laborCost = hours * LABOR_COST_PER_HOUR;
   totalCost = paintCost + laborCost;
   
   cout << fixed << setprecision(2);
   cout << "\nGallons of paint:";
   cout << setw(3) << right << gallons << endl;
   cout << "Paint Cost:";
   cout << setw(8) << right << "$" << paintCost << endl;
   cout << "Hours of labor:";
   cout << setw(6) << right << hours << endl;
   cout << "Labor cost:";
   cout << setw(8) << right << "$" << laborCost << endl;
   cout << "Total charges:";
   cout << setw(5) << right << "$" << totalCost << endl;
}
