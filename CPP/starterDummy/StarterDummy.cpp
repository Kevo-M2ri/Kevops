#include <iostream>
#include <cstring>
using namespace std;

const int MAX_CHAR = 101;
const int CAP = 100;
struct Video {
	char title[MAX_CHAR];
	int year;
};

void displayMenu();
char readOption();
void addVideo(Video list[], int &size);
void printList(Video list[], int size);
Video srchByTitle(Video list[], int size);

int main() {
	Video list[CAP];
	int size = 0;
	char option;
	do {
		displayMenu();
		option = readOption();
		switch (option) {
		case 'A':
			addVideo(list, size);
			break;
		case 'P':
			printList(list, size);
			break;
		case 'S':
			srchByTitle(list, size);
			break;
		case 'Q':
			cout << "Goodbye!" << endl;
			break;
		default:
			cout << "Invalid option. Please try again." << endl;
		}
	} while (option != 'Q');

	return 0;
}

void displayMenu() {
	cout << "(a) - Add a video" << endl;
	cout << "(p) - Print the list" << endl;
	cout << "(s) - Search by title" << endl;
	cout << "(q) - Quit" << endl;
}

char readOption() {
	char option;
	cout << "Enter your option: ";
	cin >> option;
	cin.ignore(100, '\n');
	return toupper(option);
}

void addVideo(Video list[], int &size) {
	if (size == CAP) {
		cout << "The list is full." << endl;
		return;
	}
	cout << "Enter the title: ";
	cin.getline(list[size].title, MAX_CHAR);
	cout << "Enter the year: ";
	cin >> list[size].year;
	cin.ignore(100, '\n');
	size++;
}

void printList(Video list[], int size) {
	if (size == 0) {
		cout << "The list is empty." << endl;
		return;
	}
	for (int i = 0; i < size; i++) {
		cout << list[i].title << " (" << list[i].year << ")" << endl;
	}
}

Video srchByTitle(Video list[], int size) {
	char title[MAX_CHAR];
	Video dummy;
	strcpy(dummy.title, "");
	dummy.year = 0;
	cout << "Enter the title: ";
	cin.getline(title, MAX_CHAR);
	for (int i = 0; i < size; i++) {
		if (strcmp(list[i].title, title) == 0) {
			cout << list[i].title << " (" << list[i].year << ")" << endl;
			return list[i];
		}
	}
	cout << "The title is not found." << endl;
	return dummy;
}