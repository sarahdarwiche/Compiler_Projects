#include <vector>
#include <assert.h>
#include "utilities.h"

using namespace std;

/*****************************************************************************************
 * merge sort
 ****************************************************************************************/
 
//sub-array i...j-1 is assumed sorted
//sub-array j...end is assumed sorted
//merge the two sub-arrays and store in i...end
void merge(vector<int> &array, vector<int> &temp_array, int i, int j, int end) {
  
  int start = i; //save i
  int k = 0; //starting index for copying into temp array
  
  int i_bound = j; //first array is in i...i_bound-1
  int j_bound = end + 1; //second array is in j...j_bound-1
  int number_of_elements = end-start+1; //elements in i...end
 
  while((i < i_bound) && (j < j_bound)) {
    if(array[i] < array[j]) {
      temp_array[k] = array[i];
      i++;
      k++;
    }
    else {
      temp_array[k] = array[j];
      j++;
      k++;
    }
  }
  
  assert((i==i_bound && j<j_bound) || (j==j_bound && i<i_bound));
  assert(k < number_of_elements); //k must be smaller than number of elements
  
  if(j == j_bound) { //copying rest of first half
    assert(i < i_bound); //more to copy from i-array
    int l;
    for(l = i; l < i_bound; l++) { 
      assert(k < number_of_elements);
      temp_array[k] = array[l]; 
      k++;
    }
  }
  
  if(i == i_bound) { //copying rest of second half
    assert(j < j_bound); //more to copy from j-array
    int l;
    for(l = j; l < j_bound; l++) { 
      assert(k < number_of_elements);
      temp_array[k] = array[l]; 
      k++;
    }
  } 
  
  
  //copy temp_array back to array
  int a, b;
  b = 0;
  for(a = start; a <= end; a++) {
    array[a] = std::move(temp_array[b]);
    b++;
  }
  
  
}

void merge_sort(vector<int> &array, vector<int> &temp_array, int start, int end) {
  assert(array.size()==temp_array.size());
  assert(0<=start && start<=array.size()-1);
  assert(0<=end && end<=array.size()-1);
  assert(start <= end);
  
  if(start == end) return;
  
  int mid = ( start + end ) / 2;
  
  merge_sort(array, temp_array, start, mid);
  merge_sort(array, temp_array, mid + 1, end);
  
  merge(array, temp_array, start, mid + 1, end);
  
}

void merge_sort(vector<int> &array) {
  vector<int> temp_array(array.size());
  merge_sort(array, temp_array, 0, array.size()-1);
  
  //expensive, so comment out when checked
  //assert(is_increasingly_sorted(array));
  
  //print_array(array);
  
} 

/*****************************************************************************************
 * end
 ****************************************************************************************/
 
