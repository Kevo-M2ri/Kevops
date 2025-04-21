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
        char                    itemName[MAX_CHAR];
        float                   itemPrice;
        InventoryItem   anItem;

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

int ItemList::length() const {
        return size;
}

void ItemList::changePrice(int index, float newPrice) {
        if (index >= 0 && index < size) {
                list[index].setItemPrice(newPrice);
        }
}

void addNewItems(ItemList& inventory)
{
        char choice;
        char itemName[MAX_CHAR];
        float itemPrice;

        cout << "\nWould you like to add new items to inventory? (y/n): ";
        cin >> choice;
        cin.ignore(); // Clear the newline character from buffer

        while (tolower(choice) == 'y')
        {
                cout << "Enter item name: ";
                cin.getline(itemName, MAX_CHAR);

                cout << "Enter item price: ";
                cin >> itemPrice;
                cin.ignore(); // Clear the newline character from buffer

                // Create and add the new item
                InventoryItem newItem(itemName, itemPrice);
                inventory.append(newItem);

                cout << "Item added successfully!" << endl;
                cout << "Would you like to add another item? (y/n): ";
                cin >> choice;
                cin.ignore(); // Clear the newline character from buffer
        }
}