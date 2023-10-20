#include <stdio.h>

#include "t1.h"
#include "./t1_skeleton.c"


int main(){
	int size=7;
	int arr[size];

	printf("Filling in descending order.\n");
	fill_descending(arr,size);
	printArray(arr,size);

	return 0;
}

