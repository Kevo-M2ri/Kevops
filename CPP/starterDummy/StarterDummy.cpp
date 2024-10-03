#include <iostream>
#include <string>
#include <iomanip>
#include <cmath>
#include <cstdlib>

using namespace std;

int main(){
    cout << "Welcome to my NOOB test zone!" << endl;

    int seedVal;
	int dataPoint1;
	int dataPoint2;
	int dataPoint3;
	int dataPoint4;
   int sum;

   cin >> seedVal;

   srand(seedVal);

   dataPoint1 = (rand() % 19);
   dataPoint2 = (rand() % 19);
   dataPoint3 = (rand() % 19);
   dataPoint4 = (rand() % 19);

	sum = dataPoint1 + dataPoint2 + dataPoint3 + dataPoint4;

	cout << dataPoint1 << endl;
	cout << dataPoint2 << endl;
	cout << dataPoint3 << endl;
	cout << dataPoint4 << endl;
	cout << "Sum: " << sum << endl;
    
    return 0;
}