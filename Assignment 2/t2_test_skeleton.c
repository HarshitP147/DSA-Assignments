#include <stdio.h>

#include "t1.h"
#include "t2.h"

#include "./t1_skeleton.c"
#include "./t2_skeleton.c"

int main(){
	int size=7;
	int arr[size];
	
	printf("Array before insertion sort:\n");
	
	fill_with_duplicates(arr,size);
	printArray(arr,size);

	insertionSort(arr,size);
	printf("Array after insertion sort:\n");

	printArray(arr,size);

	return 0;
}

