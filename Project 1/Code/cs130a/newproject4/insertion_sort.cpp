#include <vector>
#include <assert.h>
#include "utilities.h"
using namespace std;

/*****************************************************************************************
 * insertion sort
 ****************************************************************************************/
 
void insertion_sort(vector<int> &array) {

  int i, j, temp;
  
  for(i = 1; i < array.size(); i++) {
    for(j = i; j > 0; j--) {
      if(array[j] < array[j-1]) {
        temp = array[j-1];
        array[j-1] = array[j];
        array[j] = temp;
       }
      else {
        break;
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
