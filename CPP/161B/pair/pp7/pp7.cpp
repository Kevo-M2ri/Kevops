#include <iostream>

using namespace std;

int findMaxValue(int arr[], int size) {
    int max = 0; // Initialize max to 0
    
    for (int i = 0; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    
    return max;
}

int main() {
    int numbers[] = {-10, -5, -20, -1, -30};
    int size = sizeof(numbers) / sizeof(numbers[0]);
    
    int maxValue = findMaxValue(numbers, size);
    
    cout << "The maximum value in the array is: " << maxValue << endl;
    
    return 0;
}