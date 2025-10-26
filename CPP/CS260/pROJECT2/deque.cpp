/*  Name: Kelvin Muturi
    class: CS260
    Project: project2
*/

#include "deque.h"

// Constructor: Initializes an empty deque
Deque::Deque() : front(nullptr), rear(nullptr), count(0) {}

// Destructor: Calls clear to deallocate all nodes
Deque::~Deque() {
    clear();
}

// Adds a command to the end (rear) of the deque
void Deque::addToEnd(int sequenceNumber, const char* description) {
    Command* newCommand = new Command(sequenceNumber, description);
    
    if (rear == nullptr) { 
        // Empty deque: new command is both front and rear
        front = rear = newCommand;
    } else {
        // Link new command to the current rear
        newCommand->prev = rear;
        rear->next = newCommand;
        rear = newCommand;
    }
    
    count++;
}

// Removes and returns the command from the end (rear)
Command* Deque::removeFromEnd() {
    if (rear == nullptr) {
        return nullptr;  // Empty deque
    }
    
    Command* removedCommand = rear;
    
    if (rear == front) { 
        // Only one element: deque becomes empty
        front = rear = nullptr;
    } else {
        // Move rear pointer back and disconnect the removed node
        rear = rear->prev;
        rear->next = nullptr;
    }
    
    count--;
    removedCommand->prev = nullptr;  // Disconnect from list
    return removedCommand;
}

// Adds a command to the front of the deque
void Deque::addToFront(int sequenceNumber, const char* description) {
    Command* newCommand = new Command(sequenceNumber, description);
    
    if (front == nullptr) { 
        // Empty deque: new command is both front and rear
        front = rear = newCommand;
    } else {
        // Link new command before the current front
        newCommand->next = front;
        front->prev = newCommand;
        front = newCommand;
    }
    
    count++;
}

// Removes and returns the command from the front
Command* Deque::removeFromFront() {
    if (front == nullptr) {
        return nullptr;  // Empty deque
    }
    
    Command* removedCommand = front;
    
    if (front == rear) { 
        // Only one element: deque becomes empty
        front = rear = nullptr;
    } else {
        // Move front pointer forward and disconnect the removed node
        front = front->next;
        front->prev = nullptr;
    }
    
    count--;
    removedCommand->next = nullptr;  // Disconnect from list
    return removedCommand;
}

// Returns pointer to the rear command without removing it
Command* Deque::peekEnd() const {
    return rear;
}

// Returns pointer to the front command without removing it
Command* Deque::peekFront() const {
    return front;
}

// Displays all commands from front to rear
void Deque::display() const {
    if (front == nullptr) {
        std::cout << "Command history is empty" << std::endl;
        return;
    }
    
    // Traverse from front to rear
    Command* current = front;
    while (current != nullptr) {
        current->display();
        current = current->next;
    }
}

// Checks if the deque is empty
bool Deque::isEmpty() const {
    return front == nullptr;
}

// Returns the current size of the deque
int Deque::getSize() const {
    return count;
}

// Removes all elements from the deque
void Deque::clear() {
    while (!isEmpty()) {
        Command* temp = removeFromFront();
        delete temp;  // Free the memory
    }
}