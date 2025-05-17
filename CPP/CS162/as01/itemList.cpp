#include "itemList.h"
ItemList::ItemList()
{
	size = 0;
	capacity = CAPACITY;
}

InventoryItem& ItemList::get (int index)
{
	return list[index];
}

void ItemList::append(const InventoryItem& anItem)
{
	list[size] = anItem;
	size++;
}

void ItemList::readList(istream& in)
{
	char 			itemName[MAX_CHAR];
	float 			itemPrice;
	InventoryItem 	anItem;

	in.get(itemName, MAX_CHAR, ':');
	while (!in.eof())
	{
		in.get();
		in >> itemPrice;
		in.get();
		
		anItem.setItemName(itemName);
		anItem.setItemPrice(itemPrice);
		append(anItem);

		in.get(itemName, MAX_CHAR, ':');
	}
}
	
void ItemList::printList() const
{
	int index;

	cout << fixed;
	cout.precision(2);
	for(index = 0; index < size; index++)
	{
		list[index].print();
	}
}

int ItemList::removeItem(float maxPrice) {
	if (size == 0)
		return 0;

	int itemsRemoved = 0;
	int i = 0;

	while (i < size) {
		if (list[i]. getItemPrice() > maxPrice) {
			for (int j = i; j < size - 1; j++) {
				list[j] = list[j + 1];
			}
			size--;
			itemsRemoved++;
		}
		else {
			i++;
		}
	}
	for (int i =0; i < size - 1; i++) {
		for (int j = 0; j< size - 1 - i; j++) {
			if (list[j].isGreaterThan(list[j + 1])) {
				InventoryItem temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}

	return itemsRemoved;
}
