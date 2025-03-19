#pragma once
#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

const int MAX_SIZE = 20;;

struct Cart {
    char name[50];
    double price;
    int quantity;
};

void displayMenu();
void addItem(Cart cart[], int& itemCount);
void removeItem(Cart cart[], int& itemCount);
void updateItem(Cart cart[], int itemCount);
void displayCart(const Cart cart[], int itemCount);
void checkout(const Cart cart[], int itemCount);
int getMenuChoice();
double calculateItemTotal(const Cart& item);
double calculateCartTotal(const Cart cart[], int itemCount);
void showItemsList(const Cart cart[], int itemCount);
bool validateItemNumber(int& itemNumber, int itemCount);