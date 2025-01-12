#include <iostream>
#include <cstring>
using namespace std;

void RemoveSpaces(char userString[], char userStringNoSpaces[]);

int main() {
   char userStatement[50];
   char userStatementNoSpaces[50];
   
   cin.getline(userStatement, 50);
   
   RemoveSpaces(userStatement, userStatementNoSpaces);
   
   cout << userStatementNoSpaces << endl;

   return 0;
}

void RemoveSpaces(char userString[], char userStringNoSpaces[]){
   int j = 0;
   for (int i = 0; i < strlen(userString); i++) {
      if (userString[i] != ' ') {
         userStringNoSpaces[j] = userString[i];
         j++;
      }
   }
   userStringNoSpaces[j] = '\0';
}

