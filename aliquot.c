// This program embodies the aliquot sequence
// Required inclusions from the C library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

// Main Method
int main(int argc, char **argv) {
    // Declaring the checker variable
    char term;

    // Declaring the variables for the program
    uint64_t number;
    size_t length;
    char sequence;

    // Prompt for the staring number in the aliquot sequence
    printf("Please give the number to start the aliquot sequence from: ");
    if (scanf("%" SCNu64 "%c", &number, &term) != 2 || term != '\n') { // Check whether entered a integer
        printf("The value entered is not of type integer. Stopping.\n"); // Show error if the variable is not an integer
        exit(1); // Exit the program with exit code 1
    }

    // Prompt for the maximum length in the aliquot sequence
    printf("Provide the max aliquot length to look for (0 for unlimited): ");
    if (scanf("%lu%c", &length, &term) != 2 || term != '\n') { // Check whether entered a integer
        printf("The value entered is not of type integer. Stopping.\n"); // Show error if the variable is not an integer
        exit(1); // Exit the program with exit code 1
    }

    //Prompt for whether it should show the full sequence or just its length
    printf("Do you want to print the full sequence ('f') or just the length ('l')? ");
    scanf("%c", &sequence);
    if (sequence != 'f' && sequence != 'l') { // Check whether the value is 'l' or 'f'
        printf("The value can onle be 'f' or 'l'. Stopping.\n"); // Show error if the variable is not 'l' or 'f'
        exit(1); // Exit the program with exit code 1
    }

    uint64_t initial_number = number; // Number before changes useful for debugging
    size_t num = 0; // Initialize the variable for the loop necessery if the length from before is not 0
    char run = 1;

    while (run) { //If run is 1 run otherwise stop
        if (number == 0 || (length == 0 ? 0 : num >= length)) {
            run = 0;
            break;
        }

        ++num;

        if (sequence == 'f') printf("%" PRIu64 "\n", number); // Print the value of number

        if (number > 1e15) { // Check if the number is above 10^15
            printf("Number exceeds maximum supported integer (1000000000000000). Stopping.\n"); // Show an error if its
            exit(1); // Exit the program with exit code 1
        }

        uint64_t final = 0; // Set the default final number
        uint64_t sqrt_num = (uint64_t) sqrt(number);

        for (uint64_t i = 1; i <= sqrt_num; ++i) { // Run for every number from 1 to the square root of the number
            if (number % i == 0) { // Check if the number is divisible by i
                uint64_t paired = number / i; // Get the paired number that if multiplied with i gets the number

                if (i != number) final += i;  // Add the small divisor
        
                // Add the paired divisor if it's different from i and not the number itself
                if (paired != i && paired != number) final += paired;
            }
            
            if (argc > 1 && (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0)) // Debug
                printf("I: %" PRIu64 ", Final: %" PRIu64 "\n", i, final);
        }

        if (sequence == 'f' && number == 1) printf("%" PRIu64 "\n", final); // Print the value of final if the number is 1
        number = final; //Assign the final value to the number to rerun with the new value
    }

    if (sequence == 'l') printf("Length of aliquot sequence: %lu\n", num); //If the choice 'l' is selected print the length of the sequence

    // DEBUG
    if (argc > 1 && (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0)) {
        printf("Number: %" PRIu64 "\n", initial_number);
        printf("Length: %lu\n", length);
        printf("Sequence: %c\n", sequence);
    }

    return 0; // Finalize the program and exit with exit code 0 and finish successfully
}