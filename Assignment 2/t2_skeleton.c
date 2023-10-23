#include <stdio.h> 
#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;

void selectionSort(int arr[], int size) { 
	for(int i=0;i<size;i++){
		int minPos=i;
		for(int j=i+1;j<size;j++){
			if(arr[j]<arr[minPos]){
				minPos=j;
			}
		}
		int temp=arr[minPos];
		arr[minPos]=arr[i];
		arr[i]=temp;
	}
}

void insertionSort(int arr[],int size){
	int key,j;
	for(int i=1;i<size;i++){
		key=arr[i];
		j=i;
		while(arr[j-1]>key && j>=1){
			arr[j]=arr[j-1];
			j--;
		}
		arr[j]=key;
	}
}

int partition(int arr[],int left,int right){
	int pivot=arr[right];
	int i=left,j=right;

	while(i<j){
		if(arr[i]<=pivot){
			i++;
		}
		if(arr[j]>=pivot){
			j--;
		}
		if(i<j){
			int temp=arr[i];
			arr[i]=arr[j];
			arr[j]=temp;
		}
	}
	int temp=arr[right];
	arr[right]=arr[j];
	arr[j]=temp;

	return i;
}

void quickSort(int arr[],int left,int right){
	if(left<right){
		int pivot=partition(arr,left,right);  // find out the partition

		// implement the quick sort for both the halves
		quickSort(arr,left,pivot);
		quickSort(arr,pivot+1,right);
	}
}


