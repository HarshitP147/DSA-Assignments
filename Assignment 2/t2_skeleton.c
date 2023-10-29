#include <stdio.h> 

#include "t2.h"

int number_comparisons = 0;
int number_swaps = 0;

void selectionSort(int arr[], int size) { 
	for(int i=0;i<size;i++){
		int minPos=i;
		for(int j=i+1;j<size;j++){
			if(arr[j]<arr[minPos]){
				number_comparisons++;
				minPos=j;
			}
		}
		int temp=arr[minPos];
		arr[minPos]=arr[i];
		arr[i]=temp;
		number_swaps++;
	}
}

void insertionSort(int arr[],int size){
	int key,j;
	for(int i=1;i<size;i++){
		key=arr[i];
		j=i;
		while(arr[j-1]>key && j>=1){
			number_comparisons+=2;
			arr[j]=arr[j-1];
			j--;
		}
		arr[j]=key;
	}
}

int partition(int arr[], int left, int right) {
    int pivot = arr[left + (right - left) / 2]; // Choose the middle element as the pivot
    int i = left - 1;
    int j = right + 1;

    while (1) {
        do {
            i++;
			number_comparisons++;
        } while (arr[i] < pivot);
        do {
            j--;
			number_comparisons++;
        } while (arr[j] > pivot);

        if (i >= j){
			number_comparisons++;
            return j;
		}

        // Swap arr[i] and arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
		number_swaps++;
    }
}

void quickSort(int arr[], int size) {
    quickSortRecursive(arr, 0, size - 1);
}

void quickSortRecursive(int arr[], int left, int right) {
    if (left < right) {
        int pivot = partition(arr, left, right);
        quickSortRecursive(arr, left, pivot);
        quickSortRecursive(arr, pivot + 1, right);
    }
}

void merge(int arr[],int mid,int left,int right){
	// get the size of two arrays 
	int n1=mid-left+1,n2=right-mid;
	
	int arr1[n1],arr2[n2];

	for(int i=0;i<n1;i++){
		arr1[i]=arr[left+i];
	}

	for(int j=0;j<n2;j++){
		arr2[j]=arr[j+mid+1];
	}


	// now merge the two arrays
	int i=0,j=0,k=left;
	while(i!=n1 && j!=n2){
		if(arr1[i]<arr2[j]){
			arr[k]=arr1[i++];
		}
		else{
			arr[k]=arr2[j++];
		}
		k++;
	}

	// incase some elements are remaining in the arrays
	while(i<n1){
		arr[k++]=arr1[i++];
	}
	while(j<n2){
		arr[k++]=arr2[j++];
	}
 }

void mergeSortRecursive(int arr[],int left,int right){
	if(left<right){
		int mid=(left+right)/2;
		mergeSortRecursive(arr,left,mid);
		mergeSortRecursive(arr,mid+1,right);

		merge(arr,mid,left,right);
	}
}

void mergeSort(int arr[],int size){
	mergeSortRecursive(arr,0,size);
}

