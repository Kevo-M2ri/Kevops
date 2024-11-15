#include <iostream>
using namespace std;

int main() {
   int inputValue;
   int i;
   int j;

   cin >> inputValue;
   
   char quiz = '?';
   for (i = 1; i <= inputValue; ++i) {
      for (j = 1; j <= i; ++j) {
         cout << quiz;
      }
      cout << i << endl;
   }

   return 0;
}