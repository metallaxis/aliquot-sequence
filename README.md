# Aliquot Sequence

## How it works
1. The program prompts the user for a starting number and maximum sequence length, validating all inputs.

2. In the main loop, it computes the next number in the sequence as the sum of all proper divisors of the current number:
    * Iterates from 1 up to the square root of the number.
    * Adds each divisor and its corresponding paired divisor, excluding the number itself and duplicate divisors.

3. The sum becomes the new number in the sequence. The loop continues until the number reaches zero or the maximum sequence length is reached.

4. Depending on the user’s choice, the program either prints the full sequence or only the total length of the sequence.

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
4
3
1
0
```

## Cloning
```sh
git clone https://github.com/progintro/hw0-metallaxis.git
```

## Compiling
After cloning the repository run the following command:
```sh
make build (windows/linux)
```
To run use:
```sh
make run linux
```
(to run on windows you need to execute it manually)

## Sources / Extra Info
[Aliquot Sequence](https://en.wikipedia.org/wiki/Aliquot_sequence.)<br>
[HW0 Webpage](https://progintro.github.io/assets/pdf/hw0.pdf)<br>
