CS 162 Computer Science II
Assessment 1 (Classes)
===================================

-----------------------------------
Academic Integrity
-----------------------------------

You may NOT, under any circumstances, begin an assessment by looking for
completed code on StackOverflow or Chegg or any such website, which you can
claim as your own. Please check out the Student Code of Conduct at PCC.  This
assessment is individual work only. You must not discuss this assessment with
any person other than your instructor. You may use course material for
reference but you must not use any other (non-course) material during this
assessment. I may ask you to explain your assessment verbally. If you cannot
satisfactorily explain what your code does, and answer questions about why you
wrote it in a particular way, then you should expect a zero.

This is the ACTUAL Assessment. This assessment focuses on the implementation
of C++ classes.

This is a timed assessment, individual work only. Please do not discuss this
assessment with any person other than the instructor.

Please be sure to submit something before the deadline! Late submissions are
not accepted and will receive a zero score. Submitting something, even if it
does not work as well as you would like, is always better than not submitting
anything and receiving a zero score!

-----------------------------------
Overview
-----------------------------------

This assessment comes with several files containing code. These are the files
you will be looking and editing to complete the tasks.

Use the provided makefile to compile your code:

To compile: make
To run: ./main
To clean up: make clean

Your output should look like this:

Current Inventory:
apple           0.99
banana          0.69
cookie          0.50
donut           1.00
egg         3.88
fish        5.88
milk        2.99
yogurt          6.38

Now go through the provided files so you understand what is in there and then
start working on the Tasks outlined below.

You can modify the provided source files, header files and makefile as
needed. The file items.txt contains a set of sample data which is used by the
program to populate the inventory. You are not allowed to use <string>,
<vector> or any other header files in STL.

Check out the Sample Runs at the end of this section

-----------------------------------
Tasks
-----------------------------------

For this test, you will need to complete the following tasks:
1) Create isGreaterThan member function for class InventoryItem. It should compare the passed in item with the invoking item by name.

bool isGreaterThan(const InventoryItem& anItem) const;

        step 1: add the function prototype to class InventoryItem in item.h,
        step 2: put the function implementation in item.cpp
        step 3: invoke/test the function in main.

You need to read in the item to be compared from the user. When reading in from user, you can read in individual attributes, then invoke the set functions in InventoryItem class. Please label your output clearly.

Sample invoking code:

Inventory item1, item2;

//read in attributes for the items and set them up
...

if(item1.isGreaterThan(item2))
{
        cout << "item1 > item2" << endl;
}

2) Create a public member function to remove all the items that cost above the given price from the inventory. The inventory should stay sorted by item name after the removal. The function returns the number of items removed if the removal is successful and it returns 0 if there are no items matching the criteria or the array is empty.

int removeItem(float maxPrice);

        step 1: add the public member function prototype inside class ItemList in itemList.h
        step 2: put the member function implementation in itemList.cpp
        step 3: invoke/test the function in main.
                a. You need to read in the max price from the user.
                b. You need to display the list after testing the removeItem function.
                c. Please label your output clearly.


Use the provided makefile to compile your code:

To compile: make
To run: ./main
To check memory leaks: valgrind –leak-check=full ./main
To clean up: make clean
"readme.txt" 184L, 6009C                 