#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <math.h>

// Declarations of the two functions you will implement
// Feel free to declare any helper functions or global variables
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int search_recursive(int i, int j, char** arr, int** path, char* word, int index, int* pathorder);
int bSize;

// Main function, DO NOT MODIFY 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

    // Read the size of the puzzle block
    fscanf(fptr, "%d\n", &bSize);
    
    // Allocate space for the puzzle block and the word to be searched
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));

    // Read puzzle block into 2D arrays
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    
    // Print out original puzzle grid
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    
    // Call searchPuzzle to the word in the puzzle
    searchPuzzle(block, word);
    
    return 0;
}

char custom_tolower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

void printPuzzle(char** arr) {
	// This function will print out the complete puzzle grid (arr). 
    // It must produce the output in the SAME format as the samples 
    // in the instructions.
    // Your implementation here...
    int n = strlen(*arr);
    for (int i = 0; i < n; i++){
		for(int j = 0; j < n - 1; j++){
			printf("%c  ", *(*(arr + i) + j));
		}
		printf("%c\n", *(*(arr + i) + n - 1));
	}

    printf("\n");
}

int search_recursive(int i, int j, char** arr, int** path, char* word, int index, int* pathorder) {
    int n = strlen(*arr);

    // check if indices are within bounds
    if (i < 0 || i >= n || j < 0 || j >= n) {
        return 0;
    }

    char arr_char = custom_tolower(*(*(arr + i) + j));
    char word_char = custom_tolower(*(word + index - 1));

    // check if current character matches the corresponding character in the word
    if (arr_char != word_char) {
        return 0;
    }

    // mark the current position as visited
    *(*(path + i) + j) = index;

    *(pathorder + index) = i * n + j;

    // check if the entire word has been found
    if (index == strlen(word)) {
        return 1;
    }

    // recursively search in all possible directions
    for (int i_offset = -1; i_offset <= 1; i_offset++) {
        for (int j_offset = -1; j_offset <= 1; j_offset++) {
            if (i_offset == 0 && j_offset == 0) {
                continue;  // skip the current cell
            }
            if (search_recursive(i + i_offset, j + j_offset, arr, path, word, index + 1, pathorder)) {
                return 1;  // word found in a valid path
            }
        }
    }

    *(pathorder + index) = 0;
    // if the word is not found in any direction, reset the current position
    *(*(path + i) + j) = 0;

    return 0;
}


void searchPuzzle(char** arr, char* word) {
    // This function checks if arr contains the search word. If the 
    // word appears in arr, it will print out a message and the path 
    // as shown in the sample runs. If not found, it will print a 
    // different message as shown in the sample runs.
    // Your implementation here...

    int n = strlen(*arr);

    // allocate memory for new path arr and vars
    int** path = (int**)malloc(n * sizeof(int*));
    int* pathorder = (int*)malloc((strlen(word) + 1) * sizeof(int));
    for(int i = 0; i < n; i++){
        *(path + i) = (int*)malloc(n * sizeof(int));
        for(int j = 0; j < n; j++){
            *(*(path + i) + j) = 0;
        }
    }

    // look for the first letter in arr
    int found = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            if(custom_tolower(*(*(arr + i) +j)) == custom_tolower(word[0])){
                found = search_recursive(i,j,arr,path,word,1,pathorder);
                break;
            }
        }
        if (found == 1){break;}
    }

    if (found == 1) {
        // word found! Implement logic to process the path based on path array
        printf("Word found!\nPrinting the search path:\n");
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int index = *(*(path + i) + j);
                if (index == 0) {
                    printf("%15s", "0"); 
                } else {
                    // find the order of this character in the search path
                    int order = 0;
                    while (pathorder[order] != i * n + j) {
                        order++;
                    }
                    // calculate the number of spaces needed before the number
                    int leading_spaces = 15 - (int)(log10(order) + 1);
                    // print the leading spaces and then the order
                    printf("%*d", leading_spaces, order);
                    // check if there's another occurrence of the same character in the path
                    for (int k = order + 1; k <= strlen(word); k++) {
                        if (pathorder[k] == i * n + j) {
                            // print additional occurrences of the same character without spacing
                            printf("%d", k);
                        }
                    }
                }
            }

            printf("\n");
        }
    } else {
        printf("Word not found.\n");
    }
}