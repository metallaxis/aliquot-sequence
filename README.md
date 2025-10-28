# Aliquot Sequence

## How it works
For this project, I used variables of types unsigned int, uint64_t, and char. At the beginning of the program, the user is asked to enter a number to start the sequence. If any value other than a number is entered, the program terminates and displays an error message informing the user that an invalid input was provided. The same validation applies when entering the sequence length and when choosing whether to print the entire sequence or only its length. After each valid input, the program executes the clear() function to clean the input buffer and avoid issues with subsequent inputs. Next comes the program’s main loop, where, if the user has chosen the option ('f'), it prints each number in the sequence, while if ('l') is selected, it only calculates the length. Inside the loop, a check ensures that if the number exceeds 10^15, the program stops and notifies the user. Then, a loop begins from 1 up to the square root of the initial number. If the division of the number by a potential divisor is exact, that divisor is added to a new variable (final). The corresponding “paired” divisor — the number obtained by dividing the initial number by the current divisor — is also added, as long as it is not equal to the divisor itself or to the number. Finally, the sum of all divisors becomes the new number, and the process repeats until the value reaches zero or the maximum sequence length is reached. If the user has selected to display only the length ('l'), the program prints the total length of the aliquot sequence before terminating successfully.

## Example
```
λ ./aliquot
Please give the number to start the aliquot sequence from: 12
Provide the max aliquot length to look for (0 for unlimited): 0
Do you want to print the full sequence ('f') or just the length ('l')? f
12
16
15
9
9
4
3
1
0
```

## Cloning
```bash
git clone https://github.com/progintro/hw0-metallaxis.git
```

## Compiling
```bash
gcc -O0 -m32 -Wall -Wextra -Werror -pedantic -o aliquot aliquot.c
```

## Sources / Extra Info
[Aliquot Sequence](https://en.wikipedia.org/wiki/Aliquot_sequence.)<br>
[HW0 Webpage](https://progintro.github.io/assets/pdf/hw0.pdf)<br>
