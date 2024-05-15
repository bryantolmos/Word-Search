# Word Search - Bryant Olmos

Word Search is a past project of mine where I implemented the `searchPuzzle()` function. 

It reads a puzzle and searches for a word inputed by a user, if word is found then a search
path is printed, if word is not found, then it states so.

## How this program works
1. When the program starts, it reads the puzzle grid from a text file and save it as 
   a 2-D character array. (The first number in the text file containing the puzzle grid indicates the size of the grid.
   For instance, a 5 means the puzzle is a 5 × 5 grid.)
3. The program will then ask the user for the word to search and store it in the variable `word`.
4. The program prints the original puzzle grid and searches for the word in the puzzle.
5. The program then prints whether the search word is found, if so, a search path of that word is printed


## searchPuzzle(char**, char*) 
This function is the core of the program. It takes in the puzzle grid to find the search word 
input by the user (the 2nd argument) and it prints the phrase `Word found!` and the path(s) if the word is found. 
If the word is not found, it prints `Word not found`.
#### Limitations of `searchPuzzle`
* The search is case insensitive
* All directons are allowed
* The letters must be at most one index away from each other in row or column or both
* No array notation `[]`, only pointer notation allowed
* Creating helper functions is allowed

## My work
I implemented the `searchPuzzle` functions using a recursive approach to explore all possible paths heres how:

### `printPuzzle`
* Function to print out 2D char array representing the puzze grid
* Iterates through the 2D array and prints out each character

    ```diff
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
    ```
  

