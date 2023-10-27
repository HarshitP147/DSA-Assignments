#include <stdio.h>

#include "t1.h"
#include "t2.h"

#include "./t1_skeleton.c"
#include "./t2_skeleton.c"

int main(){
	int size=7;
	int arr[size];

	printf("Ascending array:\n");
	printf("Array before quick sort:\n");
	fill_ascending(arr,size);
	printArray(arr,size);
	quickSort(arr,size);
	printf("Array after quick sort:\n");
	printArray(arr,size);
	printf("Number of comparisons:%d\n",number_comparisons);
	printf("Number of swaps:%d\n\n",number_swaps);

	printf("Descending array:\n");
	printf("Array before quick sort:\n");
	fill_descending(arr,size);
	printArray(arr,size);
	quickSort(arr,size);
	printf("Array after quick sort:\n");
	printArray(arr,size);
	printf("Number of comparisons:%d\n",number_comparisons);
	printf("Number of swaps:%d\n\n",number_swaps);

	printf("Uniformly filled array:\n");
	printf("Array before quick sort:\n");
	fill_uniform(arr,size);
	printArray(arr,size);
	quickSort(arr,size);
	printf("Array after quick sort:\n");
	printArray(arr,size);
	printf("Number of comparisons:%d\n",number_comparisons);
	printf("Number of swaps:%d\n\n",number_swaps);

	printf("With Duplicates array:\n");
	printf("Array before quick sort:\n");
	fill_with_duplicates(arr,size);
	printArray(arr,size);
	quickSort(arr,size);
	printf("Array after quick sort:\n");
	printArray(arr,size);
	printf("Number of comparisons:%d\n",number_comparisons);
	printf("Number of swaps:%d\n\n",number_swaps);

	printf("Without Duplicates array:\n");
	printf("Array before quick sort:\n");
	fill_without_duplicates(arr,size);
	printArray(arr,size);
	quickSort(arr,size);
	printf("Array after quick sort:\n");
	printArray(arr,size);
	printf("Number of comparisons:%d\n",number_comparisons);
	printf("Number of swaps:%d\n",number_swaps);

	return 0;
}

