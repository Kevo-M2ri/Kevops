/*      Name: Kelvin Muturi
 *      Class: CS260
 *      Project: project2
*/

#include "deque.h"

// Constructor(empty deque)
Deque::Deque() : front(nullptr), rear(nullptr), count(0) {}

// Destructor(all nodes deallocation)
Deque::~Deque() {
	clear();
}

// add command to the end of deque constructor
void Deque::addToEnd(int sequenceNumber, const char* description) {
	Command* newCommand =  new Command(sequenceNumber, description);

	if (rear == nullptr) {
		front = rear = newCommand;
	}
	else {
		// link new command to the current rear
		newCommand->prev = rear;
		rear->next = newCommand;
		rear = newCommand;
	}

	count++;
}

// method to remove and return command from the end
Command* Deque::removeFromEnd() {
	if (rear ==nullptr) {
		return nullptr; // empty deque
	}

	Command* removedCommand = rear;

	if (rear == front) {
		front = rear = nullptr;
	}
	else {
		rear = rear->prev;// move rear pointer back
		rear->next = nullptr;//disconnect removed node
	}

	count--;
	removedCommand->prev = nullptr;//disconnect from list
	return removedCommand;
}

//method to add command to the front of the deque
void Deque:addToFront(int sequenceNumber, const char* description) {
	Command* newCommand = new Command(sequenceNumber, description);

	if (front == nullptr) {
		front = rear =newCommand;
	}
	else {
		newCommand->next = front;
		front->prev = newCommand;
		front = newCommand;
	}

	count++;
}

//method to remove and return command from the front
Command* Deque::removeFromFront() {
	if (front == nullptr) {
		return nullptr;//empty deque
	}

	Command* removedCommand = front;

	if (front == rear) {
		front = rear = nullptr;
	}
	else {
		front = front->next;// move front pointer forward
		front->prev = nullptr;// disconnect the removed node
	}

	count--;
	removedCommand->next = nullptr;// disconnect from list
	return removedCommand;
}

// method to return pointer to the rear command without removing it
Command* Deque::peekEnd() const {
	return rear;
}

// method to return pointer to the front command without removing it
Command* Deque::peekFront() const {
	return front;
}

// method to display all commands from front to rear
void Deque::display() const {
	if (front == nullptr) {
		cout << "Command history is empty" << endl;
		return;
	}
	// traverse from front to rear
	Command* current = front;
	while(current != nullptr) {
		current->display();
		current = current->next;
	}
}

// method to check if deque is empty
bool Deque::isEmpty() const {
	return front == nullptr;
}

// method to return current size of the deque
int Deque::getSize() const {
	return count;
}

// method to remove all elements from the deque
void Deque::clear() {
	while(!isEmpty()) {
		Command* temp = removeFromFront();
		delete temp; //free the memory
	}
}
