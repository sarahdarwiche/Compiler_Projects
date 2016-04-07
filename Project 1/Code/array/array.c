#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "array.h"



int small_and_large(int* arr, int size){
	int i;
	int small;
	int large;
	
	small = arr[0];
	large = arr[0];
	
	for(i=0; i<size; i++){
		if( arr[i] < small) small = arr[i];
		if( arr[i] > large) large = arr[i];
	}
	
	printf("smallest is %d \n", small);
	printf("largest is %d \n", large);
	
	return 0;
}

int* fill_ar(int* arr, int size)
{
	int i;
	
	/* Intializes random number generator */
    srand (time(NULL));
	
	for(i=0; i < size; i++) {
		arr[i] = rand() % 50;
	}
	return arr;
	
}

void print_ar(int* arr, int size)
{
	int i;
	
	for(i=0; i<size; i++){
		printf("Element in position %d is %d \n",i, arr[i]);
	}
	printf("\n");
}

int main(int argc, char** argv) {
	int* array1;
	int* array2;
	int size;
	int i;
	               ////////////need to fix array 1 and array 2 are always the same
	               
	size = 7;
	
	array1 = (int *)malloc(size * sizeof(int));
	array1 = fill_ar(array1, size);
	
	array2 = (int *)malloc(size * sizeof(int));
	array2 = fill_ar(array2, size);
	
	
	print_ar(array1, size);
	small_and_large(array1,size);
	
	printf("\n");
	
	print_ar(array2, size);
	small_and_large(array2,size);
	
	return 0;
}