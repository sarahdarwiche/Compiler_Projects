#include <vector>
using namespace std;

/*****************************************************************************************
 * merge sort
 ****************************************************************************************/
 
void merge(vector<int> &array, vector<int> &temp_array, int i, int j, int end) {
  int start = i;
  int k = 0;
  int i_bound = j;
  int j_bound = end + 1;
  
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
  
  if(j == j_bound) { //copying rest of first half
    int l;
    for(l = i; l < j; l++) { 
      temp_array[k] = array[l];
      k++;
      }
    }
  
  if(i == i_bound) { //copying rest of second half
    int l;
    for(l = j; l <= end; l++) { 
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
  if(start == end) return;
  
  int mid = ( start + end ) / 2;
  
  merge_sort(array, temp_array, start, mid);
  merge_sort(array, temp_array, mid + 1, end);
  
  merge(array, temp_array, start, mid + 1, end);
  
}

void merge_Sort(vector<int> &array) {
  
  vector<int> temp_array(array.size());
  merge_sort(array, temp_array, 0, array.size()-1);
}

/*****************************************************************************************
 * end
 ****************************************************************************************/
