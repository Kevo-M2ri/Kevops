/**----------------------------------------------------------------------------
   Author:      Kelvin Muturi
   Date:        February 9, 2025
   Assignment:  CS-161B Assignment midterm exam
   Description: This program implements a queue using an array. The program
                allows the user to dequeue an element from the queue, print the
                queue, and quit the program.
   Inputs:      command as a character, value to dequeue as an integer.
   Outputs:     queue as an integer, dequeue result as an array, error messages.
   -------------------------------------------------------------------------**/
#include <iostream>

using namespace std;

int dequeue(int queue[], int &size, int &val);
void printQueue(int queue[], int size);

const int MAX = 3; // maximum size of queue

int main() {
    int queue[MAX] = {8, -2, 3}; // integer array for queue
    int size = 3;   // contains number of elements in queue
    char command; // command to be read from input
    int val; // value to be read from input
    int result; // result of dequeue operation
    
    do {
        cout << "Enter a command; (q to quit), (d to dequeue), (p to print): ";
        cin >> command; // read command from input

        switch (command) {
            case 'd':
                cout << "Enter value to dequeue: ";
                cin >> val; // read value from input

                result = dequeue(queue, size, val); // call dequeue function

                if (result == 1) {
                    cout << "Dequeue failed: Queue is empty" << endl;
                }
                else if (result == 2) {
                    cout << "Dequeue failed: Value cannot found" << endl;
                }
                break;
            case 'p': // print queue
                printQueue(queue, size);
                break;
            case 'q':
                cout << "Quitting..." << endl;
                break;
            default:
                cout << "Error! Invalid command" << endl;
        }
    } while(command != 'q');// loop until command is 'q'
    
    return 0;
}

//this function removes the first occurrence of val from the queue,
// and returns 0 if successful, 1 if the queue is empty, and 2 if the value is not found
int dequeue(int queue[], int &size, int &val){
    int index;
    int anotherSize;

    if (size == 0){
        return 1; //Empty queue
    }

    index = -1; //initialize index to -1

    for (int i = 0; i < size; i++){
        if (queue[i] == val){
            index = i;
            break;
        }
    }

    if (index == -1){
        return 2; // value not found
    }

    anotherSize = size - index - 1; // number of elements after the index
    for (int i = 0; i < anotherSize; i++){
        queue[i] = queue[index + 1 + i];
    }
    size = anotherSize; // update size

    return 0; //success
}

// Call this function to print the queue
void printQueue(int queue[], int size){
    cout << "[";
    for (int i = 0; i < size; i++){
        cout << queue[i];
        
        if (i != size - 1)
            cout << ", " ;
    }
    cout << "]" << endl;
}