#include "deque.h"

Deque::Deque() : front(nullptr), rear(nullptr), size(0) {}

Deque::~Deque() {
    clear();
}

void Deque::addToEnd(int sequence_number, const char* description) {
    Command* new_command = new Command(sequence_number, description);
    
    if (rear == nullptr) { // Empty deque
        front = rear = new_command;
    } else {
        new_command->prev = rear;
        rear->next = new_command;
        rear = new_command;
    }
    
    size++;
}

Command* Deque::removeFromEnd() {
    if (rear == nullptr) {
        return nullptr;
    }
    
    Command* removed_command = rear;
    
    if (rear == front) { // Only one element
        front = rear = nullptr;
    } else {
        rear = rear->prev;
        rear->next = nullptr;
    }
    
    size--;
    removed_command->prev = nullptr;
    return removed_command;
}

void Deque::addToFront(int sequence_number, const char* description) {
    Command* new_command = new Command(sequence_number, description);
    
    if (front == nullptr) { // Empty deque
        front = rear = new_command;
    } else {
        new_command->next = front;
        front->prev = new_command;
        front = new_command;
    }
    
    size++;
}

Command* Deque::removeFromFront() {
    if (front == nullptr) {
        return nullptr;
    }
    
    Command* removed_command = front;
    
    if (front == rear) { // Only one element
        front = rear = nullptr;
    } else {
        front = front->next;
        front->prev = nullptr;
    }
    
    size--;
    removed_command->next = nullptr;
    return removed_command;
}

Command* Deque::peekEnd() const {
    return rear;
}

Command* Deque::peekFront() const {
    return front;
}

void Deque::display() const {
    if (front == nullptr) {
        std::cout << "Command history is empty" << std::endl;
        return;
    }
    
    Command* current = front;
    while (current != nullptr) {
        current->display();
        current = current->next;
    }
}

bool Deque::isEmpty() const {
    return front == nullptr;
}

int Deque::getSize() const {
    return size;
}

void Deque::clear() {
    while (!isEmpty()) {
        Command* temp = removeFromFront();
        delete temp;
    }
}