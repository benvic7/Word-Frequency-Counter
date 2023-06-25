/**
 * @DESCRIPTION: This program reads a text file and [file this in]. The file name is provided using command line 
 * arguments. If the file name is not provided or if the file is not readable, the program will exit
 * and provide an error message.
 *
 * @AUTHOR: Ben Vicinelli {vicibj20@wfu.edu}
 * @DATE: Feb. 8, 2023
 * @ASSIGNMENT: Lab 3
 * @COURSE: CSC 250
 **/

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_STRING_SIZE 20



/* INITIALIZING THE WORDFREQ STRUCT */
/* each struct holds the word in a string (character array) and a counter for the number of times the word appears */
struct WordFreq {
    char* word;
    int count;
};



/* FUNCTION DECLARATIONS */
/*function that processes each character from the input file*/
int process_characters(char filename[], char output[]);
/*function that checks if the word has already been seen*/
int is_found(char buf[], struct WordFreq **wfpp, int size);
/*function that adds the word if it has not already been seen*/
struct WordFreq ** add_word(char buf[], struct WordFreq **wfpp, int size);
/*function that sorts the words by count (number of times each word has been seen)*/
struct WordFreq ** bubble_sort(struct WordFreq **wfpp, int size);
/*function that prints the sorted words to the output file*/
int print_results(char output[], struct WordFreq **wfpp, int size);



/* MAIN METHOD */
int main(int argc, char* argv[]){
    /* initializing fileOK */
    int fileOK;
    fileOK = 1;

    /* if less than 3 files are given (we need lab3.c, input file, and output file) */
    if(argc < 3){
        printf("Usage: %s filename frequency_file \n", argv[0]);
        return 1;
    }

    /* calling process_characters */
    fileOK = process_characters(argv[1], argv[2]);

    /* if we cannto open the file */
    if(!fileOK){
        printf("%s could not open file %s \n", argv[0], argv[1]);
        return 2;
    }

    return 0;
}


/* FUNCTION THAT PROCESSES EACH CHARACTER FROM THE INPUT FILE */
int process_characters(char filename[], char output[]){
    /* initializing the file pointer */
    FILE *filePtr;
    /* used as the index for the for loop at the end of the function */
    int i;
    /* n is the size of the buffer array*/
    int n;
    /* size is the number of unique words that have been read so far */
    int size;
     /* index is the index of the current word */
    int index;
    /* ch temporarily holds each character */
    char ch;
    /* buffer temporarily holds the current word*/
    char *buffer;
    /* another temporary buffer */
    char *str_buff;
    /* first_word is true only when it is the first word of the file */
    bool first_word;
    /* the struct pointer to a pointer */
    struct WordFreq **wfpp;
    /* initializing variables */
    i = 0;
    n = 0;
    size = 0;
    index = 0;
    buffer = (char *) malloc(sizeof(char) * MAX_STRING_SIZE);
    first_word = true;

    /* initialize pointers to null */
    filePtr = NULL;
    wfpp = NULL;

    /* initialize wfpp, which is a pointer to a pointer to a struct */
    wfpp = (struct WordFreq**) malloc(sizeof(struct WordFreq *));
    /* then initialize the first pointer in the pointer array, which points to the struct, which holds the word and count for each word */
    wfpp[0] = (struct WordFreq*) malloc(sizeof(struct WordFreq));
    /* increment size by 1 because we have read in the first word */
    size = 1;


    /* open the file that we are reading from, or print that it could not be open if we can't open it*/
    filePtr = fopen(filename, "rie");
    if(filePtr == 0) {
        printf("Could not open %s \n", filename);
        return 0;
    }


    /* gets the next (first) character in the file */
    ch = fgetc(filePtr);


    /* runs until we reach the end of the file */
    while(ch != EOF) {

        /* if we reach the end of a word (because max length is 20)*/
        if (n >= 19) {

            /* copying the buffer to str_buff (so that when we change str_buff, buffer is not changed)*/
            str_buff = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
            strcpy(str_buff, buffer);

            /* if it is the first word, change the boolean and allocate the word and count to the struct*/
            if (first_word == true) {
                first_word = false;
                wfpp[0] -> word = str_buff;
                wfpp[0] -> count = 1;
            }

            else {
                /* call the is_found method */
                index = is_found(str_buff, wfpp, size);

                /* if the word is found, increase it's count by 1 */
                if (index > -1) {
                    wfpp[index] -> count = wfpp[index] -> count + 1;
                }

                /* if the word is not found, call the add_word method, which allocates a new word to memory and sets its count to 1 */
                else {
                    wfpp = add_word(str_buff, wfpp, size);
                    /* increase the total number of unique words read so far */
                    size = size + 1;
                }
            }
            /* reset buffer and index */
            buffer[0] = '\0';
            n = 0;
        }
        
        /* if the nect character is a letter (indicating we are on the same word) */
        if (isalpha(ch)) {
            /* makes it lowercase */
            ch = tolower(ch);
            /* add the character to the buffer */
            buffer[n] = ch;
            /* increment the size of the buffer*/
            n = n + 1;
            /* moves the escape character to the end of the buffer */
            buffer[n] = '\0';
        }
        
        else if (n > 0){
            
            /* copying the buffer to str_buff (so that when we change str_buff, buffer is not changed)*/
            str_buff = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
            strcpy(str_buff, buffer);

            /* if it is the first word, change the boolean and allocate the word and count to the struct*/
            if (first_word == true) {
                first_word = false;
                wfpp[0] -> word = str_buff;
                wfpp[0] -> count = 1;
            }

            else {
                /* call the is_found method */
                index = is_found(str_buff, wfpp, size);

                /* if the word is found, increase it's count by 1 */
                if (index > -1) {
                    wfpp[index] -> count = wfpp[index] -> count + 1;
                }

                /* if the word is not found, call the add_word method, which allocates a new word to memory and sets its count to 1 */
                else {
                    wfpp = add_word(str_buff, wfpp, size);
                    /* increase the total number of unique words read so far */
                    size = size + 1;
                }
            }

            /* reset buffer and size of the buffer array */
            buffer[0] = '\0';
            n = 0;
        }
        /* move to the next character */
        ch = fgetc(filePtr);
    }


    /* if a word was found but not processed before EOF */
    if (strlen(buffer) > 0) {
        printf("X %d, %s\n", n, buffer);
        str_buff = (char *) malloc(sizeof(char) * (strlen(buffer) + 1));
        strcpy(str_buff, buffer);
        /*check if the word is already in a struct */
        index = is_found(str_buff, wfpp, size);
        /* increase the count at the position of the word if it is */
        if (index > -1){
            wfpp[index]->count = wfpp[index] -> count + 1;
        }
        else {
            wfpp = add_word(str_buff, wfpp, size);
            size = size + 1;
        }
    }


    /* after going through the whole file, sort the words by frequency*/
    wfpp = bubble_sort(wfpp, size);

    /* print the words */
    print_results(output, wfpp, size);

    /* finally, we can close the file */
    fclose(filePtr);


    /* need to de-allocate the heap no longer needed.
    This must be done since the pointers are local function variables on the stack */
    for (i = 0; i < size; i++) {
        free((void *) wfpp[i] -> word);
        free((void *) wfpp[i]);
    }

    free((void *)buffer);
    free((void *)str_buff);
    free((void *)wfpp);

    return 1;
}



/* FUNCTION THAT CHECKS IF THE WORD HAS ALREADY BEEN SEEN */
int is_found(char buf[], struct WordFreq **wfpp, int size) {
    /* initialize the index */
    int i;
    i = 0;

    /* run the loop until we have gone through all words that have been read so far */
    for (i= 0; i < size; i++) {
        
        /* if the string buffer (current word) equals any word we have already seen, then we return the "index" of that word */
        if (strcmp(buf, wfpp[i] -> word) == 0) {
            return i;
        }
    }

    /* if a match is not found, then we return -1 (to indicate we need to add the word) */
    return -1;
}



/* FUNCTION THAT ADDS THE WORD IF IT HAS NOT ALREADY BEEN SEEN */
struct WordFreq ** add_word(char buf[], struct WordFreq **wfpp, int size) {
    
    /* reallocating a new memory space for our new word */
    wfpp = (struct WordFreq**) realloc((void*) wfpp, (sizeof(struct WordFreq *) * (size + 1)));
    /* at that memory space, create a new pointer to the struct, initialize the word in the char array and set the count to 1 */
    wfpp[size] = (struct WordFreq*) malloc(sizeof(struct WordFreq));
    wfpp[size] -> word = buf;
    wfpp[size] -> count = 1;

    /* return the pointer to a pointer to the struct */
    return wfpp;
}



/* FUNCTION THAT SORTS THE WORDS BY COUNT (NUMBER OF TIMES EACH WORD HAS BEEN SEEN) */
struct WordFreq ** bubble_sort(struct WordFreq **wfpp, int size) {
    /* initialize the indexes for the for loops */
    /* i did not initialize each index to 0 because when I did that, the sort did not run correctly, so I initialized them inside the loops */
    int i;
    int j;

    /* wfp is a temporary pointer (used for the swap) */
    struct WordFreq *wfp;

    /* nested for loop to check each word against every other word */
    for (i = 0; i < size - 1; i++) {
        for (j = 0; j < (size - 1 - i); j++) {
            if (wfpp[j] -> count < wfpp[j + 1] -> count) {
                /* bubble sort */
                wfp = wfpp[j];
                wfpp[j] = wfpp[j + 1];
                wfpp[j + 1] = wfp;
            }
        }
    }

    /* return the pointer to a pointer to the struct */
    return wfpp;
}



/* FUNCTION THAT PRINTS THE SORTED WORDS TO THE OUTPUT FILE */
int print_results(char output[], struct WordFreq **wfpp, int size) {
    /* initialize variables */
    FILE *outputFilePtr;
    int i;

    /* open the file we are printing to, or print that it could not be open if we can't open it*/
    outputFilePtr = fopen(output, "w");
    if (outputFilePtr == 0) {
        printf("Could not open %s\n", output);
        return 0;
    }

    /* print each word and its count to the output file*/
    for (i = 0; i < size; i++) {
        fprintf(outputFilePtr, "%s %d\n", wfpp[i] -> word, wfpp[i] -> count);
    }

    /* close the file */
    fclose(outputFilePtr);
    return 1;
}