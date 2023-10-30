#include <stdio.h>

#include "t1.h"
#include "./t1_skeleton.c"

void bubbleSort(int arr[], int n) {
   int i, j, temp;
   for (i = 0; i < n-1; i++) {     
       for (j = 0; j < n-i-1; j++) {
           if (arr[j] > arr[j+1]) {
               temp = arr[j];
               arr[j] = arr[j+1];
               arr[j+1] = temp;
           }
       }
   }
}

int partition(int arr[], int low, int high) {
   int pivot = arr[high]; 
   int i = (low - 1); 
   int temp;

   for (int j = low; j <= high - 1; j++) {
       if (arr[j] < pivot) {
           i++; 
           temp = arr[i];
           arr[i] = arr[j];
           arr[j] = temp;
       }
   }
   temp = arr[i + 1];
   arr[i + 1] = arr[high];
   arr[high] = temp;
   return (i + 1);
}

void quickSort(int arr[], int low, int high) {
   if (low < high) {
       int pi = partition(arr, low, high);
       quickSort(arr, low, pi - 1);
       quickSort(arr, pi + 1, high);
   }
}


int main(){
	int size=7;
	int arr[size];

	printf("Filling in descending order.\n");
	fill_descending(arr,size);
	printArray(arr,size);

	return 0;
}

