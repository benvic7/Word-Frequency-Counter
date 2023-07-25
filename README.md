# Word Frequency Counter

## Description
This program reads a text file and calculates the number of times each word appears in the file. The program then returns a new file listing the count for each word sorted by frequency. The file names are provided as a command-line arguments.

## Author
- Ben Vicinelli
- Date: Feb. 8, 2023

## Features
- Uses structs and pointers for word-frequency pairs: each word is represented as a character array and its corresponding frequency is stored as an integer in dynamically allocated memory.
- Implements bubble sort to sort words by frequency: the program uses the bubble sort algorithm to efficiently arrange words in descending order based on their frequency.
- Proper Memory Management: the program dynamically allocates and deallocates memory for words and data structures to avoid memory leaks and handle variable-sized inputs efficiently.

## Functionality
### `process_characters(char filename[], char output[])`
This function processes each character from the input file, extracts words, and calculates their frequencies. It uses pointers and dynamic memory allocation to store words and their counts in the struct array.

### `is_found(char buf[], struct WordFreq **wfpp, int size)`
Checks if a word has already been seen in the struct array. It uses pointers to efficiently access the words for comparison.

### `add_word(char buf[], struct WordFreq **wfpp, int size)`
Adds a new word to the struct array if it has not been seen before. The function dynamically allocates memory for the new word and count using pointers.

### `bubble_sort(struct WordFreq **wfpp, int size)`
Sorts the words in the struct array based on their frequency using the bubble sort algorithm. It uses pointers to efficiently swap struct elements during sorting.

### `print_results(char output[], struct WordFreq **wfpp, int size)`
Prints the sorted words and their frequencies to the output file. The function efficiently accesses the struct elements using pointers.

## How to Use
1. Compile the code using a C compiler: `gcc word_frequency_counter.c -o word_frequency_counter`
2. Run the program with the input and output file names as command-line arguments: `./word_frequency_counter input_file.txt output_file.txt`
3. The program will read the input file, calculate word frequencies, sort the words by frequency in descending order, and save the results in the output file.

## Note
Please ensure that the input file is readable and contains valid text data. If the file cannot be opened or contains non-text characters, the program will display an error message and exit.
