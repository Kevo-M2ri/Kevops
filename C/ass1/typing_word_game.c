#define _BSD_SOURCE
#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
        //variables definition
        const char* words[] = {
                "The", "quick" , "brown", "fox", "jumps", "over","the", "lazy", "dog"}; //default words
        int numWords = sizeof(words) / sizeof(words[0]); //count of words calculation
        const char* shuffledWords[numWords]; //empty array with 9 string pointers
        char input[260]; // buffer to hold user input

        //struct for time
        struct timeval tv_seed1; //current time declaration
        gettimeofday(&tv_seed1, NULL); //current time
        srand(tv_seed1.tv_usec); //microseconds seed generator

        struct timeval start, end, difference; //start,end and difference declaration

        printf("This is a game that tests typing speed\n\n");
        for (int i = 0; i < numWords; i++) {
                shuffledWords[i] = words[i];
        }
        // shuffle (had to google this one Fisher-Yates Algorithm)
        for (int i = numWords - 1; i > 0; i--) {
                int j = rand() % (i + 1); //random position
                const char* temp = shuffledWords[i];
                shuffledWords[i] = shuffledWords[j];
                shuffledWords[j] = temp;
        }

        printf("Type the following words as fast as you can:\n");

        gettimeofday(&start, NULL); //start of timer

        for (int i = 0; i < numWords; i++) {
                while(1) {
                        printf("  word #%d is %s: ", i + 1, shuffledWords[i]);

                        if(scanf("%259s", input) != 1) {
                                printf("Error reading input.Try again.\n");
                                return 1;
                        }

                    if(strcmp(input, shuffledWords[i]) == 0) {
                                break;
                        }
                        else{
                                printf("Incorrect! Try again.\n");
                        }
                }
        }

        gettimeofday(&end, NULL);

        timersub(&end, &start, &difference);

        printf("You completed the typing test in %ld seconds %ld usec.\n", (long)difference.tv_sec, (long)difference.tv_usec);

}
                                                