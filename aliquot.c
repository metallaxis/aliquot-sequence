/*

    This program embodies the aliquot sequence

*/

// Required inclusions from the C library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

// Main Method
int main(int argc, char **argv) {
    // Initialize the checker variable
    char term;

    // Initialize the variables for the program
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
    printf("Do you want to print the full sequence ('f') or just the length ('l')? ");
    scanf("%c", &sequence);
    if (sequence != 'f' && sequence != 'l') { // Check whether the value is 'l' or 'f'
        printf("The value can onle be 'f' or 'l'. Stopping.\n"); // Show error if the variable is not 'l' or 'f'
        exit(1); // Exit the program with exit code 1
    }

    size_t num = 0; // Initialize the variable for the loop necessery if the length from before is not 0
    do { // Run once then check the loop
        if (length != 0) ++num;

        if (number > 1e15) {
            printf("Number exceeds maximum supported integer (1000000000000000). Stopping.\n");
            exit(1); // Exit the program with exit code 1
        }

        uint64_t final = 0;

        for (uint64_t i = 1; i < number; ++i) {
            if (number % i == 0) final+=i;
            if (argc > 1 && (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0)) // Debug
                printf("Final: %" PRIu64 ", I: %" PRIu64 "\n", final, i);
        }

        if (sequence == 'f') printf("%" PRIu64 "\n", number);
        if (sequence == 'f' && number == 1) printf("%" PRIu64 "\n", final);
        number = final;
    } while ((length == 0 ? 1 : num < length) && number != 0); //If length is 0 run infinetely otherwise run until the num hits the length

    if (sequence == 'l') printf("Length of aliquot sequence: %lu", num);

    // DEBUG
    if (argc > 1 && (strcmp(argv[1], "-d") == 0 || strcmp(argv[1], "--debug") == 0)) {
        printf("Number: %" PRIu64 "\n", number);
        printf("Length: %lu\n", length);
        printf("Sequence: %c\n", sequence);
    }

    return 0; // Finalize the program and exit with exit code 0 and finish successfully
}
