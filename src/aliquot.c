// This program embodies the aliquot sequence
// Required inclusions from the C library
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

// Method declarations
uint64_t sum_of_divisors(uint64_t number, char *debug);
uint64_t mysqrt_u64(uint64_t number);
void execute_tests(char *debug);

// Main Method
int main(int argc, char **argv) {
    // Argumental Setup
    char debug = 0;
    char test = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-d") == 0 || strcmp(argv[i], "--debug") == 0)
            debug = 1;
        if (strcmp(argv[i], "-t") == 0 || strcmp(argv[i], "--test") == 0)
            test = 1;
    }

    // Execute Tests
    if (test) execute_tests(&debug);


    // Declaring the variables for the program
    char input[100];
    uint64_t number;
    unsigned int length;
    char sequence;

    
    // Prompt for the staring number in the aliquot sequence
    printf("Please give the number to start the aliquot sequence from: ");
    if (scanf("%s", input) != 1) { // Get the full string of the input
        printf("Failed reading the string from stdin. Please retry.");
        exit(1);
    }

    for (int i = strlen(input)-1; i >= 0; --i) // Run backwards from the string length to 0 (-1 to ignore the null terminator)
        if (input[i] != ' ') ungetc(input[i], stdin); // Check whether the character at index i is a space and if it is then return to stdin
    if (scanf("%" SCNu64, &number) != 1 || input[0] == '0' || input[0] == '-') { // Check whether entered an integer
        printf("The value entered is not a positive integer. Stopping.\n"); // Show error if the variable is not a positive integer
        exit(1);
    }


    // Prompt for the maximum length in the aliquot sequence
    printf("Provide the max aliquot length to look for (0 for unlimited): ");
    if (scanf("%s", input) != 1) { // Get the full string of the input
        printf("Failed reading the string from stdin. Please retry.");
        exit(1);
    }

    for (int i = strlen(input)-1; i >= 0; --i) // Run backwards from the string length to 0 (-1 to ignore the null terminator)
        if (input[i] != ' ') ungetc(input[i], stdin); // Check whether the character at index i is a space and if it is then return to stdin
    if (scanf("%u", &length) != 1 || input[0] == '-') { // Check whether entered a integer and nothing else following it
        printf("The value entered is not an integer. Stopping.\n"); // Show error if the variable is not a positive integer
        exit(1);
    }


    //Prompt for whether it should show the full sequence or just its length
    printf("Do you want to print the full sequence ('f') or just the length ('l')? ");
    // Check whether the value of sequence is 'l' or 'f' and nothing else following it
    if (scanf("%s", input) != 1) { // Get the full string of the input
        printf("Failed reading the string from stdin. Please retry.");
        exit(1);
    }
    
    for (int i = strlen(input)-1; i >= 0; --i) // Run backwards from the string length to 0 (-1 to ignore the null terminator)
        if (input[i] != ' ') ungetc(input[i], stdin); // Check whether the character at index i is a space and if it is then return to stdin
    if ((scanf("%c", &sequence) != 1) || (sequence != 'f' && sequence != 'l')) {
        printf("The value can only be 'f' or 'l'. Stopping.\n"); // Show error if the variable is not 'l' or 'f'
        exit(1);
    }


    uint64_t sum = number;
    unsigned int counter = 0;

    while (1) {
        // Check if the conditions for printing the number are met and then print the number
        if (sequence == 'f' && (length == 0 ? 1 : counter <= length)) printf("%" PRIu64 "\n", sum);

        // Check if the conditions for exiting the loop are met
        if (sum == 0 || (length == 0 ? 0 : counter > length))
            break;

        ++counter;

        if (sum > 1e15) { // Check if the sum is above 10^15
            printf("Sum exceeds maximum supported integer (10^15). Stopping.\n"); // Show an error if its
            exit(1);
        }

        sum = sum_of_divisors(sum, &debug); // Find the next number of the sequence
    }

    if (sequence == 'l') printf("Length of aliquot sequence: %u\n", counter); //If the choice 'l' is selected print the length of the sequence

    // DEBUG
    if (debug) {
        printf("Number: %" PRIu64 "\n", number);
        printf("Length: %u\n", length);
        printf("Sequence: %c\n", sequence);
    }

    return 0; // Finalize the program and exit with exit code 0 and finish successfully
}

uint64_t sum_of_divisors(uint64_t number, char *debug) {
    uint64_t sqrt_num = mysqrt_u64(number);
    uint64_t sum = 0;

    for (uint64_t i = 1; i <= sqrt_num; ++i) { // Run for every number from 1 to the square root of the number
        if (number % i == 0) { // Check if the number is divisible by i
            uint64_t paired = number / i; // Get the paired number that if multiplied with i gets the number

            if (i != number) sum += i;  // Add the small divisor
        
            // Add the paired divisor if it's different from i and not the number itself
            if (paired != i && paired != number) sum += paired;
        }
            
        if (*debug) printf("I: %" PRIu64 ", Sum: %" PRIu64 "\n", i, sum);
    }
    return sum;
}

uint64_t mysqrt_u64(uint64_t number) {
    if (number == 0) return 0.0;
    uint64_t number_copy = number;
    uint64_t y = (number_copy + 1) >> 1;

    // Integer Newton-Raphson iteration
    while (y < number_copy) {
        number_copy = y;
        y = (number_copy + number / number_copy) >> 1;
    }

    // Convert to double for fractional correction
    double dnumber_copy = (double)number_copy;
    double dnumber = (double)number;

    // One Newton refinement step in double precision
    dnumber_copy = 0.5 * (dnumber_copy + dnumber / dnumber_copy);

    return (uint64_t) dnumber_copy; // Return the square root
}

// Run tests to see if the code actually runs properly
void execute_tests(char *debug) {
    printf("Running aliquot sequence tests...\n");

    struct {
        uint64_t starting_number;
        unsigned length;
        unsigned int expected_length;
    } tests[] = {
        {12, 0, 7},
        {1, 0, 1},
        {6, 6, 7},
        {138, 200, 178},
    };

    uint64_t sum = 0;
    unsigned int counter;

    int num_tests = sizeof(tests) / sizeof(tests[0]);

    for (int t = 0; t < num_tests; t++) {
        sum = tests[t].starting_number;
        counter = 0;
        while (1) {
            if (sum == 0 || (tests[t].length == 0 ? 0 : counter > tests[t].length))
                break;

            ++counter;
            sum = sum_of_divisors(sum, debug);
        }

        if (counter == tests[t].expected_length) {
            printf("Test %d passed for starting number %" PRIu64 "\n", t, tests[t].starting_number);
        } else {
            printf("Test %d FAILED for starting number %" PRIu64 ". Got length %u, expected %u\n",
                   t, tests[t].starting_number, counter, tests[t].expected_length);
        }
    }

    exit(0);
}