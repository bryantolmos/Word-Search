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
I implemented the `searchPuzzle` functions using a recursive approach to explore all possible paths here is how
and here are my helper functions:

### `printPuzzle()`
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

### `search_recursive()`:
* Recursive function that explores all possible paths in the puzzle grid
* It checks if the current character matches the corresponding character in the word
* Marks visited positions to avoid revisiting them
* Recursively searches in all possible directions.\

  ```diff
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
    ```

### `searchPuzzle()`:
* Searches for the given word within the puzzle grid
* Utilizes a recursive approach, `search_recursive()`, to explore all possible paths
* If the word is found, it prints the search path, showing the order of characters in the word
* If the word is not found, it prints a message indicating so

  ```diff
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
  } else { printf("Word not found.\n");}
  
  }
    ```

## Output
### Using `puzzle1.txt`
#### Sample run 1:
<img width="551" alt="Screenshot 2024-05-16 at 10 08 18 PM" src="https://github.com/bryantolmos/Word-Search/assets/109110061/9baf8020-131e-441b-96ed-b65a127d6315">

#### Sample run 2:
<img width="549" alt="Screenshot 2024-05-16 at 10 09 34 PM" src="https://github.com/bryantolmos/Word-Search/assets/109110061/280fce31-fa51-466e-b2be-dbf37b8e2cd9">

### Using `puzzle2.txt`
#### Sample run 1:
<img width="658" alt="Screenshot 2024-05-16 at 10 10 37 PM" src="https://github.com/bryantolmos/Word-Search/assets/109110061/cce731d5-e609-47bc-be21-9faf2af8060f">

#### Sample run 2:
<img width="654" alt="Screenshot 2024-05-16 at 10 12 12 PM" src="https://github.com/bryantolmos/Word-Search/assets/109110061/6c3dab0a-b7ed-4a9b-9bf2-d2cbe3898a7e">

## Conclusion
Although my code is not perfect, it was a project of mine to demonstrate my proficiency and what ive learned in C for my computer organization class :)
