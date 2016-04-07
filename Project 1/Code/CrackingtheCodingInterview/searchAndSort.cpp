#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include "searchAndSort.h"


int bubbleSort(){
//start at begin of array and swap first two elements depnding on whose greater
//go on to all pairs until list is sorted
//O(n^2) worst and average case
//memory O(1) 
return 0;
}

int mybinarySearch(std::vector<int> vector, int value){
  int low = 0;
  int high = vector.size()-1;
  int middle;
  
  while( low <= high) {
     middle = low + ((high-low) / 2);
  
  	if(vector[middle] == value) {
     	std::cout << " found at postion " << position << std::endl;
     	return middle;
    }
        
    else if( vector[middle] < value ){
      //search right
      low = middle + 1;
     }
   
    else { 
      //search left
      high = middle - 1;
     }
      
  }
     std::cout << "not found" << std::endl;
     return -1;
 }
int recursiveBinarySearch(std::vector<int> &vector, int value, int low, int high){
  int middle = (low + high) / 2;
  return middle;
}

std::vector<int> fillArray(int start, int end, std::vector<int> largeArray){
	std::vector<int> subarray;
	subarray.resize(end-start);
	
	for(int i = start; i < end; i++){
		subarray[i] = largeArray[i]; 	
    }
	return subarray;
}


/*
 //mergeAll sort is O(NlogN) worst case 
void mergeAll(std::vector<int> &arrayC, std::vector<int> &temp, int start, int middle, int end){
  int aCntr, bCntr, cCntr = 0;
  std::vector<int> a,b;
  
  //fill array a, array b.
   a = fillArray(start, middle, arrayC);
   a = fillArray(middle+1, arrayC.size(), arrayC);
 
  //recursively sort array a, array b
  a = recursivemerge(a, temp, 0, middle);
  b = recursivemerge(b, temp, middle+1, b.size() );
  
  //mergeAll two sorted arrays
  while( (aCntr < a.size()) && (bCntr < b.size()) ) {
  	 if(a[aCntr] < b[bCntr]) {
  	 	arrayC[cCntr] = a[aCntr];
  	 	aCntr++;	
  	 }
  	 else {
  	 	arrayC[cCntr] = b[bCntr];
  	 	aCntr++;
  	 }
  	 cCntr++;
  }
  //copy remaining
  int remainder = middle - aCntr;
  for(int i = 0; i < remainder; i++){
		arrayC[cCntr+i] = a[aCntr+i]; 	
    }
    //no need to copy b because it's already there!
}


void recursivemerge(std::vector<int> &array, std::vector<int>&temp, int left, int right){
	
	if(left < right) {
	 	mergeMain(array, temp, left, (array.size()/2)); //sort left half
	 	mergeMain(array, temp, (array.size()/2), right); //sort right half
	 	mergeAll (array, temp,left, (array.size()/2)+1, right); //mergeAll both
	}
	
}

void recursivemerge(std::vector<int> &array){
	std::vector<int> temp = array.size();
	recursivemerge(array, temp, 0, array.size()-1);
}

*/



//int quickSort(int* S[] ){
  //int length = sizeof(S);
  //if(length == 0 || length ==1) return -1;
  //pick pivot v
  //partition into s1 and s2 
  //move start to the right and end to the left 
  //s1 = x in {S-{v} | x <= pivot}
  //s2 = x in {S-{v} | x >= pivot}
  //return quicksort(S1) + pivot + quicksort(s2)



int main(int argc, char* argv[]) {
  //add random fill
  
  // the iterator constructor can also be used to construct from arrays:
  
  std::vector<int> myvector;
  int myints[] = {3,4,7,9};
  myvector.assign (myints,myints+4);
  
  int position = mybinarySearch(myvector, 7);
  mybinarySearch(myvector, 7);
  mybinarySearch(myvector, 0);
  
  
  
  return 0;
}