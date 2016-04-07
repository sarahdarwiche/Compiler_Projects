#include <iostream>
#include <vector>
#include <assert.h>
#include "utilities.h"

using namespace std;

/*****************************************************************************************
 * bubble sort 
 ****************************************************************************************/
//pseudocode found on Wikipedia

void bubble_sort(vector<int> &array) {
  bool swapped = true;
  int length = array.size();
  while(swapped) {
    int i;
    swapped = false;
    for(i = 1; i < length; i++) {
      if(array[i-1] > array[i]) {
        swap( array[i-1], array[i]);
        swapped = true;
      }
     }
    }
  
  //expensive, so comment out when checked
  //assert(is_increasingly_sorted(array));
  
  //print_array(array);

}

/*****************************************************************************************
 * end
 ****************************************************************************************/
