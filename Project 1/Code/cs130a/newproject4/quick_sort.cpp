#include <vector>
#include <assert.h>
#include "utilities.h"

using namespace std;

/*****************************************************************************************
 * quick sort
 ****************************************************************************************/
//pseudocode found on Wikipedia


// left is the index of the leftmost element of the subarray
// right is the index of the rightmost element of the subarray (inclusive)
// number of elements in subarray = right-left+1
int partition(vector <int> &array, int left, int right) {
  int pivotIndex = left + (right-left) / 2;
  int pivotValue = array[pivotIndex];
  swap( array[pivotIndex], array[right]);
  int storeIndex = left;
  int i;
  for(i = left; i < right; i++) {
    if( array[i] <= pivotValue) {
      swap (array[i], array[storeIndex]);
      storeIndex = storeIndex + 1;
     }
    }
     swap( array[storeIndex], array[right] ); // Move pivot to its final place
     return storeIndex;
} 

void quicksort(vector<int> &array, int i, int k) {

  if (i < k) {
    int p = partition(array, i, k);
    quicksort(array, i, p - 1);
    quicksort(array, p + 1, k);
  }
}

void quick_sort(vector<int> &array) {
  int i = 0;
  int k = array.size() - 1;
  quicksort(array, i, k);
  
  //expensive, so comment out when checked
  //assert(is_increasingly_sorted(array));
  
  //print_array(array);

} 
    
/*****************************************************************************************
 * end
 ****************************************************************************************/
