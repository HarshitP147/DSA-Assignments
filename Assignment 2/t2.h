#ifndef T2_H_
#define T2_H_
void selectionSort(int arr[], int size);
void insertionSort(int arr[], int size);
int partition(int arr[],int left,int right);
void quickSort(int arr[], int left,int right);

extern int number_comparisons;
extern int number_swaps;


#endif
