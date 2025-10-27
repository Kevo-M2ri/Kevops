/*      Name: Kelvin Muturi
 *      Class: CS260
 *      Project: project2
*/

#pragma once

#include "command.h"

class Deque {
private:
	// private attributes
	Command* front; // pointer to the front of deque (for redo)
	Command* rear; // pointer to the rear of the deque(most  recent)
	int count; // number of elements in the deque

public:
	// public methods
	Deque();
	~Deque();
	Deque(const Deque& other) = delete;
	Deque& operator=(const Deque& other) = delete;
	void addToEnd(int sequenceNumber, const char* description);
	Command* removeFromEnd();
	void addToFront(int sequenceNumber, const char* description);
	Command* removeFromFront();
	Command* peekEnd() const;
	Command* peekFront() const;
	void display() const;
	bool isEmpty() const;
	int getSize() const;
	void clear();
};
