/*  Name: Kelvin Muturi
    class: CS260
    Project: project2
*/

#pragma once

#include "command.h"

class Deque {
private:
    Command* front;             // Pointer to the front of the deque (for redo)
    Command* rear;              // Pointer to the rear of the deque (most recent)
    int count;                   // Number of elements in the deque

public:
    // Constructor: Initializes an empty deque
    Deque();
    
    // Destructor: Cleans up all nodes in the deque
    ~Deque();
    
    // Prevent copying to avoid memory management issues
    Deque(const Deque& other) = delete;
    Deque& operator=(const Deque& other) = delete;
    
    // Core deque operations
    
    // Adds a new command to the end (rear) of the deque
    void addToEnd(int sequenceNumber, const char* description);
    
    // Removes and returns the command from the end (rear) of the deque
    Command* removeFromEnd();
    
    // Adds a new command to the front of the deque
    void addToFront(int sequenceNumber, const char* description);
    
    // Removes and returns the command from the front of the deque
    Command* removeFromFront();
    
    // Returns pointer to the rear command without removing it
    Command* peekEnd() const;
    
    // Returns pointer to the front command without removing it
    Command* peekFront() const;
    
    // Displays all commands in the deque from front to rear
    void display() const;
    
    // Returns true if the deque is empty
    bool isEmpty() const;
    
    // Returns the number of elements in the deque
    int getSize() const;
    
    // Utility functions
    
    // Removes all elements from the deque
    void clear();
};