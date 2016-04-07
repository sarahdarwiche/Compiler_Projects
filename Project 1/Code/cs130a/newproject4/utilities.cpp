#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <assert.h>
using namespace std;

/*****************************************************************************************
 * array input/output
 ****************************************************************************************/

vector<int> read_array(vector<int> &array){
  int i, size, temp_element;
  cin >> size; //read in array size
  
  for(i = 0; i < size; i++) {
    cin >> temp_element;
    array.push_back(temp_element);
   }
  return array;
}

void print_array(vector<int> array){
  int i;
  for(i = 0; i < array.size(); i++) {
    cout << array[i] << " ";
  }
  cout << endl;
}

/*****************************************************************************************
 * generates arrays of size n, each containing numbers from 1 to n
 ****************************************************************************************/
 
//the elements of the array are in increasing order
void get_increasing_array(vector<int> &array, int n) {  //fill empty vector in increasing order
  assert(array.size()==0); //ensures that the function is called on an empty array
  int i;
  for(i = 1; i <= n; i++) {
    array.push_back(i);
  }
  assert(array.size()==n);
}

//the elements of the array are of decreasing order
void get_decreasing_array(vector<int> &array, int n) {  //fill empty vector in decreasing order
  assert(array.size()==0);  //ensures that the function is called on an empty array
  int i;
  for(i = n; i >= 1; i--) {
    array.push_back(i);
  }
  assert(array.size()==n);
}


int my_rand(int n) {  //returns a number between 0 and n-1
  return (rand() % n);
}

//the elements of the array are ordered randomly
void get_random_array(vector<int> &array, int n) {  //generate array in random order
  assert(array.size()==0);  //ensures that the function is called on an empty array
  int i;
  for(i = 1; i <= n; i++) { //fill array in increasing order
    array.push_back(i);
  }
  for(i = array.size()-1; i > 0; i--) { //shuffle in reverse
    int random = my_rand(i+1);
    int temp;
    temp = array[i];
    array[i] = array[random];
    array[random] = temp;
  }
  assert(array.size()==n);
}


/*****************************************************************************************
 * tests that an array is sorted increasingly
 ****************************************************************************************/
 
bool is_increasingly_sorted(vector<int> &array) {
  int i;
  for(i = 0; i < array.size()-1; i++) { // don't need to check last index
    if(array[i] > array[i+1]) return false;
   }
   return true;
}

/*****************************************************************************************
 * end
 ****************************************************************************************/
