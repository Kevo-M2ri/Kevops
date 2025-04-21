#include "item.h"

InventoryItem::InventoryItem()
{
	strcpy(itemName, "no item");
	itemPrice = 0;
}

void InventoryItem::setItemName(const char name[])
{
	strcpy(itemName, name);
}

const char* InventoryItem::getItemName() const
{
	return itemName;
}

void InventoryItem::setItemPrice(float price)
{
	itemPrice = price;
}

float InventoryItem::getItemPrice() const
{
	return itemPrice;
}

void InventoryItem::print() const
{
	cout << itemName << "\t" << itemPrice << endl;
}

bool InventoryItem::isGreaterThan(const InventoryItem& anItem) const {
	return (strcmp(itemName, anItem.getItemName()) > 0);
}
