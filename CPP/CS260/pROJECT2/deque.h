#ifndef DEQUE_H
#define DEQUE_H

#include "command.h"

class Deque {
private:
    Command* front;
    Command* rear;
    int size;

public:
    Deque();
    ~Deque();
    Deque(const Deque& other) = delete; // Prevent copying
    Deque& operator=(const Deque& other) = delete; // Prevent assignment
    
    // Core deque operations
    void addToEnd(int sequence_number, const char* description);
    Command* removeFromEnd();
    void addToFront(int sequence_number, const char* description);
    Command* removeFromFront();
    Command* peekEnd() const;
    Command* peekFront() const;
    void display() const;
    bool isEmpty() const;
    int getSize() const;
    
    // Utility functions
    void clear();
};

#endif