// Write your functions in this file.
#include "clist.h"

using namespace std;

// iteratively count nodes in circular linked list
int count(node* head) {
	if (head == nullptr) {
		return 0;
	}

	int counter = 0;
	node* current = head;

	// Traverse until come back to head
	do {
		counter++;
		current = current->next;
	} while (current != head);

	return counter;
}

int countRHelper(node* current, node* head);

// Recursively counting nodes
int countR(node* head) {
	if (head == nullptr) {
		return 0;
	}

	return countRHelper(head, head);
}

// Recursive helper function for counting
int countRHelper(node* current, node* head) {
	if (current->next == head) {
		return 1;
	}
	else {
		return 1 + countRHelper(current->next, head);
	}
}

// Helper function for recursive sum
int sum(node* head) {
	if (head == nullptr) {
		return 0;
	}

	int total = 0;
	node* current = head;

	do {
		total += current->data;
		current = current->next;
	} while (current != head);

	return total;
}

int sumRHelper(node* current, node* head);

// Recursively compute sum of data
int sumR(node* head) {
	if (head == nullptr) {
		return 0;
	}

	return sumRHelper(head, head);
}

int sumRHelper(node* current, node* head) {
	if (current->next == head) {
		return current->data;
	}
	else {
		current->data + sumRHelper(current->next, head);
	}
}
