#pragma once
#include "item.h"

const int CAPACITY = 100;
class ItemList
{
private:
	InventoryItem	list[CAPACITY];
	int		size;
	int 	capacity;
	
public:
	ItemList();
	InventoryItem& get (int index);
	void append(const InventoryItem& anItem);

	void printList() const;
	void readList(istream& in);
	int removeItem(float maxPrice);
};
