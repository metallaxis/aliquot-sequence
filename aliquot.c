// This program embodies the aliquot sequence
// Required inclusions from the C library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

double mysqrt_u64(uint64_t x);

// Main Method
int main(int argc, char **argv) {
    // Declaring the checker variables
    char first, term;

    // Declaring the variables for the program
    uint64_t number;
    unsigned int length;
    char sequence;

    // Prompt for the staring number in the aliquot sequence
    printf("Please give the number to start the aliquot sequence from: ");
    if (scanf("%c", &first) != 1 || first == '\n') { // Check whether entered an empty line/space as an argument
        printf("You didn't enter a value. Stopping.\n"); // Show error if no value was entered
        exit(1); // Exit the program with exit code 1
    } else if (first != ' ') { // Check if first is a space
        ungetc(first, stdin); // Return the value to be picked up since it is not null
    }
    if (scanf("%" SCNu64 "%c", &number, &term) != 2 || term != '\n') { // Check whether entered a integer and nothing else following it
        printf("The value entered is not of type integer. Stopping.\n"); // Show error if the variable is not an integer
        exit(1); // Exit the program with exit code 1
    }

    // Prompt for the maximum length in the aliquot sequence
    printf("Provide the max aliquot length to look for (0 for unlimited): ");
    if (scanf("%c", &first) != 1 || first == '\n') { // Check whether entered an empty line as an argument
        printf("You didn't enter a value. Stopping.\n"); // Show error if no value was entered
        exit(1); // Exit the program with exit code 1
    } else if (first != ' ') { // Check if first is a space
        ungetc(first, stdin); // Return the value to be picked up since it is not null
    }
    if (scanf("%u%c", &length, &term) != 2 || term != '\n') { // Check whether entered a integer and nothing else following it
        printf("The value entered is not of type integer. Stopping.\n"); // Show error if the variable is not an integer
        exit(1); // Exit the program with exit code 1
    }

    //Prompt for whether it should show the full sequence or just its length
    printf("Do you want to print the full sequence ('f') or just the length ('l')? ");
    // Check whether the value of sequence is 'l' or 'f' and nothing else following it
    if (scanf("%c", &first) != 1 || first == '\n') { // Check whether entered an empty line as an argument
        printf("You didn't enter a value. Stopping.\n"); // Show error if no value was entered
        exit(1); // Exit the program with exit code 1
    } else if (first != ' ') { // Check if first is a space
        ungetc(first, stdin); // Return the value to be picked up since it is not null
    }
    if ((scanf("%c%c", &sequence, &term) != 2 || term != '\n') || (sequence != 'f' && sequence != 'l')) {
        printf("The value can only be 'f' or 'l'. Stopping.\n"); // Show error if the variable is not 'l' or 'f'
        exit(1); // Exit the program with exit code 1
    }

    uint64_t initial_number = number; // Number before changes useful for debugging
    unsigned int num = 0; // Initialize the variable for the loop necessery if the length from before is not 0

    while (1) { // Run till it breaks out of the loop below
        if (sequence == 'f' && (length == 0 ? 1 : num <= length)) printf("%" PRIu64 "\n", number); // Print the value of number

        if (number == 0 || (length == 0 ? 0 : num > length)) // Check whether the program exit conditions are met
            break; // Exit out the while loop

        ++num; // Incremeant num by 1

        if (number > 1e15) { // Check if the number is above 10^15
            printf("Number exceeds maximum supported integer (1000000000000000). Stopping.\n"); // Show an error if its
            exit(1); // Exit the program with exit code 1
        }

        uint64_t final = 0; // Set the default final number
        uint64_t sqrt_num = (uint64_t) mysqrt_u64(number);

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

        number = final; //Assign the final value to the number to rerun with the new value
    }

    if (sequence == 'l') printf("Length of aliquot sequence: %u\n", num); //If the choice 'l' is selected print the length of the sequence

    // DEBUG
    if (argc > 1 && (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0)) {
        printf("Number: %" PRIu64 "\n", initial_number);
        printf("Length: %u\n", length);
        printf("Sequence: %c\n", sequence);
    }

    return 0; // Finalize the program and exit with exit code 0 and finish successfully
}

double mysqrt_u64(uint64_t n) {
    if (n == 0) return 0.0; // If the number is 0 just return 0
    uint64_t x = n;
    uint64_t y = (x + 1) >> 1; // Set y to (x+1) and then shift it by one bit to the right

    // Integer Newton-Raphson iteration
    while (y < x) { // Run while y < x
        x = y; // Set x to the value of y
        y = (x + n / x) >> 1; // Shift the number (x+(n/x)) by 1 bit to the right
    }

    // Convert to double for fractional correction
    double d = (double)x;
    double dn = (double)n;
    // One Newton refinement step in double precision
    d = 0.5 * (d + dn / d);
    return d; // Return the square root
}
