#include <stdio.h>
#include <stdlib.h>
#include "t1.h"

//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size){
	 for(int i=0;i<size;i++){
		array[i]=i;
	}
}
//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size){
	for(int i=0;i<size;i++){
		array[i]=size-i-1;
	}
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size){
    int x=4;
	for(int i=0;i<size;i++){
		array[i]=x;
	}
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed.
void fill_with_duplicates(int *array, int size){
	int x = rand()%size;
	for(int i=0;i<size;i++){
		array[i]=x;
		x=rand()%size;
	}
}


//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int arr[],int size){
	
	// Create an array to track which numbers have been used.
    int *used = (int *)malloc(size * sizeof(int));
    if (used == NULL) {
        // Handle memory allocation failure.
        return;
    }

    // Initialize the used array to all zeros (indicating no numbers used yet).
    for (int i = 0; i < size; i++) {
        used[i] = 0;
    }

    // Fill the array with unique, shuffled numbers.
    for (int i = 0; i < size; i++) {
        int unique = 0;
        while (!unique) {
            int random_num = rand() % size; // Generate a random number.

            if (used[random_num] == 0) {
                arr[i] = random_num;
                used[random_num] = 1; // Mark the number as used.
                unique = 1;
            }
        }
    }

    free(used); // Don't forget to free the used array.
}


void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
  	printf("%d ", arr[i]);
  }
  printf("\n");
}

