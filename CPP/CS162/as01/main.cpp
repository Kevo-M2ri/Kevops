#include "main.h"

int main(int argc, char ** argv)
{
	ItemList		inventory;
	char			fileName[] = "items.txt";
	float			maxPrice;
	int			removed;

	//open file to read data and populate inventory
	ifstream		in;
	in.open(fileName);
	if(!in)
	{
		cerr << "Fail to open " << fileName << " for input!" << endl;
		return 1;
	}
	inventory.readList(in);
	in.close();

	cout << endl << "Current Inventory: " << endl;
	inventory.printList();

	//invoke your functions here to do what is required
	InventoryItem item1, item2;
	char item1Name[MAX_CHAR], item2Name[MAX_CHAR];
	float item1Price, item2Price;

	//testing isGreaterThan function
	cout << "Enter first item name: ";
	cin.getline(item1Name, MAX_CHAR);
	cout << "Enter first item price: ";
	cin >> item1Price;
	cin.ignore();

	cout << "Enter second item name: ";
	cin.getline(item2Name, MAX_CHAR);
	cout << "Enter second item price: ";
	cin >> item2Price;
	cin.ignore();

	item1.setItemName(item1Name);
	item1.setItemPrice(item1Price);
	item2.setItemName(item2Name);
	item2.setItemPrice(item2Price);

	cout << "\nComparing items:" << endl;
	cout << "Item 1: ";
	item1.print();
	cout << "Item 2: ";
	item2.print();

	if (item1.isGreaterThan(item2)) {
		cout << "Result: item1 > item2 (alphabetically)" << endl;
	}
	else {
		cout << "Result: item2 <= item2 (alphabetically)" << endl;
	}

	cout << endl << "Updated Inventory: " << endl;	
	inventory.printList();

	//Testing removeItem function
	cout << "Enter the maximum price (Items with prices above this amount will be removed): ";
	cin >> maxPrice;
	cin.ignore();

	removed = inventory.removeItem(maxPrice);

	cout << "\nRemoved " << removed << " items with price greater than $" << fixed << setprecision(2) << maxPrice << endl;

	cout << "Inventory after removal:" << endl;
	inventory.printList();

	return 0;
}
