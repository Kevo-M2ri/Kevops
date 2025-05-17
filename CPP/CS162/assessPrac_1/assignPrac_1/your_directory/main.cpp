#include "main.h"

int main(int argc, char ** argv)
{
	ItemList		inventory;
	char			fileName[] = "items.txt";

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

	//invoke your functions here to do what is required
	InventoryItem newItem("Orange" , 0.54);
	inventory.append(newItem);

	cout << endl << "Current Inventory: " << endl;	
	inventory.printList();

	//implementation of length() function
	cout << endl << "Number of items in inventory: " << inventory.length() << endl;

	cout << endl << "Current Inventory: " << endl;
	inventory.printList();

	//changePrice function implemented
	cout << endl << "Changing price of item 0 to 15.0" << endl;
	inventory.changePrice(0, 15.0);

	//print updated inventory4
	cout << endl << "updated Inventory: " << endl;
	inventory.printList();

	return 0;
}
