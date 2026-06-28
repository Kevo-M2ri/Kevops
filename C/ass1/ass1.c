#define _BSD_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>


int main(int argc, char *argv[]) {
    // Array of words to be used in the program

    printf("This is a game that tests typing speed\n\n");
    const char* words[] = {"The", "quick", "brown", "fox", "jumps", "over", "the", "lazy", "dog"};
    int numWords = sizeof(words) / sizeof(words[0]);
    //printf("Number of words: %d\n", num_words);

    const char* shuffledWords[numWords];

    for (int i = 0; i < numWords; i++) {
        shuffledWords[i] = words[i];
        //printf("shuffledWords: %s\n", shuffledWords[i]);
    }
    
    //generating a random seed using usec field
    struct timeval tv_seed1;
    gettimeofday(&tv_seed1, NULL);
    srand(tv_seed1.tv_usec);

    //Generating a random permutation to shuffle the words
    for (int i = numWords - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        const char* temp = shuffledWords[i];
        shuffledWords[i] = shuffledWords[j];
        shuffledWords[j] = temp;
    }

    printf("Type the following words as fast as you can:\n");

    struct timeval start, end, difference;
    gettimeofday(&start, NULL);

    char input[260]; // Buffer to hold user input
    for (int i = 0; i < numWords; i++) {
        while(1) {
            printf("   word #%d is %s: ", i + 1, shuffledWords[i]);

            if (scanf("%259s", input)!= 1) {
                printf("Error reading input. Please try again.\n");
                // Clear the input buffer
                return 1;
                
            }

            if (strcmp(input, shuffledWords[i]) == 0) {
                break;
            }
            else {
                printf("Incorrect! Try again.\n");
            }
        }
    }

    gettimeofday(&end, NULL);

    timersub(&end, &start, &difference);

    printf("You completed the typing test in %ld sec %ld usec.\n", (long)difference.tv_sec, (long)difference.tv_usec);

    return 0;
}